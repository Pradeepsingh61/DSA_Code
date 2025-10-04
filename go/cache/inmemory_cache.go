package yagcache

import (
	"errors"
	"fmt"
	"runtime"
	"sync"
	"time"
)

const (
	NoExpiration   time.Duration = -1 // Constant to indicate no expiration
	Defaultexpires time.Duration = 0  // Constant to use default expiration time
)

// Item represents a cache entry holding a value and its expiration timestamp
type Item[V any] struct {
	value   V     // Stored value
	expires int64 // Expiration time in UnixNano (0 or negative means no expiration)
}

// Internal cache struct (not exposed directly)
type cache[K ~string, V any] struct {
	mu         sync.RWMutex   // Mutex for thread-safe access
	items      map[K]*Item[V] // Actual map storing cache items
	done       chan struct{}  // Channel to stop cleanup goroutine
	expTime    time.Duration  // Default expiration time for items
	cleanupInt time.Duration  // Interval between cleanup runs
}

// Exposed Cache type embedding the internal cache
type Cache[K ~string, V any] struct {
	*cache[K, V]
}

// Time Complexity: O(1)
// Space Complexity: O(1)
// Creates a new internal cache instance
func newCache[K ~string, V any](expTime, cleanupInt time.Duration, item map[K]*Item[V]) *cache[K, V] {
	c := &cache[K, V]{
		mu:         sync.RWMutex{},
		items:      item,
		expTime:    expTime,
		cleanupInt: cleanupInt,
		done:       make(chan struct{}),
	}
	return c
}

// Time Complexity: O(1)
// Space Complexity: O(1)
// Public API: creates and returns a new cache instance with optional background cleanup
func New[K ~string, V any](expTime, cleanupTime time.Duration) *Cache[K, V] {
	items := make(map[K]*Item[V])
	c := newCache(expTime, cleanupTime, items)

	if cleanupTime > 0 {
		// Start background cleanup
		go c.cleanup()
		// Set finalizer to stop cleanup when cache is garbage collected
		runtime.SetFinalizer(c, stopCleanup[K, V])
	}

	return &Cache[K, V]{c}
}

// Time Complexity: O(1)
// Space Complexity: O(1)
// Adds a new item to the cache, returns error if key already exists
func (c *Cache[K, V]) Set(key K, val V, d time.Duration) error {
	item, err := c.Get(key)
	if item != nil && err == nil {
		return fmt.Errorf("item with key '%v' already exists. Use the Update method", key)
	}
	c.add(key, val, d)
	return nil
}

// Time Complexity: O(1)
// Space Complexity: O(1)
// Adds a value using default expiration
func (c *Cache[K, V]) SetDefault(key K, val V) error {
	return c.Set(key, val, Defaultexpires)
}

// Time Complexity: O(1)
// Space Complexity: O(1)
// Internal method to add or update a cache item
func (c *Cache[K, V]) add(key K, val V, d time.Duration) error {
	var exp int64

	// Handle expiration logic
	if d == Defaultexpires {
		d = c.expTime
	}
	if d > 0 {
		exp = time.Now().Add(d).UnixNano()
	} else if d < 0 {
		exp = int64(NoExpiration)
	}

	// Prevent overwriting existing items
	item, err := c.Get(key)
	if item != nil && err != nil {
		return fmt.Errorf("item with key '%v' already exists", key)
	}

	// Optional value validation
	switch any(val).(type) {
	case string:
		if len(any(val).(string)) == 0 {
			return fmt.Errorf("value of type string cannot be empty")
		}
	}

	// Add to map with write lock
	c.mu.Lock()
	c.items[key] = &Item[V]{value: val, expires: exp}
	c.mu.Unlock()

	return nil
}

// Time Complexity: O(1)
// Space Complexity: O(1)
// Retrieves a cache item if it exists and is not expired
func (c *Cache[K, V]) Get(key K) (*Item[V], error) {
	c.mu.RLock()
	if item, ok := c.items[key]; ok {
		if item.expires > 0 {
			now := time.Now().UnixNano()
			if now > item.expires {
				c.mu.RUnlock()
				return nil, fmt.Errorf("item with key '%v' expired", key)
			}
		}
		c.mu.RUnlock()
		return item, nil
	}
	c.mu.RUnlock()
	return nil, fmt.Errorf("item with key '%v' not found", key)
}

// Safely retrieves the value from an Item
func (it *Item[V]) Val() V {
	var v V
	if it != nil {
		return it.value
	}
	return v
}

// Time Complexity: O(1)
// Space Complexity: O(1)
// Updates an existing cache item
func (c *Cache[K, V]) Update(key K, val V, d time.Duration) error {
	item, err := c.Get(key)
	if item != nil && err != nil {
		return err
	}
	return c.add(key, val, d)
} // Time Complexity: O(1)
// Space Complexity: O(1)

// Time Complexity: O(1)
// Space Complexity: O(1)
// Deletes a cache item
func (c *Cache[K, V]) Delete(key K) error {
	c.mu.Lock()
	defer c.mu.Unlock()
	return c.delete(key)
}

// Time Complexity: O(1)
// Space Complexity: O(1)
// Internal delete logic
func (c *cache[K, V]) delete(key K) error {
	if _, ok := c.items[key]; ok {
		delete(c.items, key)
		return nil
	}
	return fmt.Errorf("item with key '%v' does not exists", key)
}

// Deletes all expired items from the cache
func (c *cache[K, V]) DeleteExpired() error {
	var err error
	now := time.Now().UnixNano()

	c.mu.Lock()
	for k, item := range c.items {
		if now > item.expires && item.expires != int64(NoExpiration) {
			if e := c.delete(k); e != nil {
				err = errors.Join(err, e)
			}
		}
	}
	c.mu.Unlock()

	return errors.Unwrap(err)
}

// Clears all items from the cache
func (c *Cache[K, V]) Flush() {
	c.mu.Lock()
	c.items = make(map[K]*Item[V])
	c.mu.Unlock()
}

// Returns the underlying items map (shallow copy not made)
func (c *Cache[K, V]) List() map[K]*Item[V] {
	c.mu.RLock()
	defer c.mu.RUnlock()
	return c.items
}

// Time Complexity: O(1)
// Space Complexity: O(1)
// Returns the count of items in the cache
func (c *Cache[K, V]) Count() int {
	c.mu.RLock()
	n := len(c.items)
	c.mu.RUnlock()
	return n
}

// Bulk inserts items into the cache
func (c *Cache[K, V]) MapToCache(m map[K]V, d time.Duration) error {
	var err error
	for k, v := range m {
		e := c.Set(k, v, d)
		err = errors.Join(err, e)
	}
	return errors.Unwrap(err)
}

// Checks if a specific key is expired
func (c *Cache[K, V]) IsExpired(key K) bool {
	item, err := c.Get(key)
	if item != nil && err != nil {
		if item.expires > time.Now().UnixNano() {
			return true
		}
	}
	return false
}

// Background cleanup process to remove expired items periodically
func (c *cache[K, V]) cleanup() {
	tick := time.NewTicker(c.cleanupInt)
	for {
		select {
		case <-tick.C:
			c.DeleteExpired()
		case <-c.done:
			tick.Stop()
			return
		}
	}
}

// Time Complexity: O(1)
// Space Complexity: O(1)
// Finalizer to stop cleanup goroutine when cache is GC'd
func stopCleanup[K ~string, V any](c *cache[K, V]) {
	c.done <- struct{}{}
}
