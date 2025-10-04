//this is to test inmemory_cache.go

package inmemory_cache

import (
	"testing"
	"time"
)

type TestStruct struct {
	Num      int
	Children []*TestStruct
}

func TestCache(t *testing.T) {
	tc := New[string, int](NoExpiration, 0)

	a, found := tc.Get("a")
	if found == nil {
		t.Error("Getting A found value that shouldn't exist:", a)
	}

	b, found := tc.Get("b")
	if found == nil {
		t.Error("Getting B found value that shouldn't exist:", b)
	}

	c, found := tc.Get("c")
	if found == nil {
		t.Error("Getting C found value that shouldn't exist:", c)
	}

	tc.Set("a", 1, NoExpiration)

	x, found := tc.Get("a")
	if found != nil {
		t.Error("a was not found while getting a2:", x)
	}

}

func TestCacheTimes(t *testing.T) {

	tc := New[string, int](50*time.Millisecond, 1*time.Millisecond)
	tc.Set("a", 1, Defaultexpires)
	tc.Set("b", 2, NoExpiration)
	tc.Set("c", 3, 20*time.Millisecond)
	tc.Set("d", 4, 70*time.Millisecond)
}
