import java.util.Arrays;

/**
 * Data Structure: Fenwick Tree (Binary Indexed Tree)
 * Description: Supports efficient prefix sums and point updates on an array.
 *
 * Operations:
 *  - update(index, delta): add delta to element at 1-based index
 *  - prefixSum(index): sum of elements in [1..index]
 *  - rangeSum(l, r): sum of elements in [l..r]
 *
 * Time Complexity: O(log n) per update/query
 * Space Complexity: O(n)
 */
public class FenwickTree {
    private final int n;
    private final long[] bit; // 1-based BIT storing partial sums

    /**
     * Construct an empty Fenwick Tree of size n (1..n).
     */
    public FenwickTree(int n) {
        if (n < 0) throw new IllegalArgumentException("n must be non-negative");
        this.n = n;
        this.bit = new long[n + 1];
    }

    /**
     * Construct Fenwick Tree from an initial array (1-based indexing implied).
     * arr is treated as 0-based; arr[i] corresponds to index (i+1).
     */
    public FenwickTree(int[] arr) {
        if (arr == null) throw new IllegalArgumentException("array cannot be null");
        this.n = arr.length;
        this.bit = new long[n + 1];
        // Build in O(n log n)
        for (int i = 0; i < n; i++) {
            update(i + 1, arr[i]);
        }
    }

    /**
     * Adds delta to element at position idx (1-based index).
     */
    public void update(int idx, long delta) {
        if (idx <= 0 || idx > n) throw new IndexOutOfBoundsException("index out of bounds: " + idx);
        for (int i = idx; i <= n; i += i & -i) {
            bit[i] += delta;
        }
    }

    /**
     * Computes prefix sum in [1..idx] (1-based index).
     */
    public long prefixSum(int idx) {
        if (idx < 0) throw new IndexOutOfBoundsException("index must be >= 0: " + idx);
        if (idx > n) idx = n; // clamp
        long sum = 0;
        for (int i = idx; i > 0; i -= i & -i) {
            sum += bit[i];
        }
        return sum;
    }

    /**
     * Range sum on [l..r] (1-based indices). Returns 0 if l>r.
     */
    public long rangeSum(int l, int r) {
        if (l > r) return 0L;
        if (l < 1 || r < 1 || l > n || r > n) {
            throw new IndexOutOfBoundsException("range out of bounds: [" + l + "," + r + "]");
        }
        return prefixSum(r) - prefixSum(l - 1);
    }

    /**
     * Optional: finds smallest index such that prefixSum(index) >= target.
     * Returns n+1 if no such index exists.
     */
    public int findByPrefixSum(long target) {
        if (target <= 0) return (target == 0) ? 0 : 1;
        int idx = 0;
        int bitMask = highestPowerOfTwo(n);
        for (int step = bitMask; step != 0; step >>= 1) {
            int next = idx + step;
            if (next <= n && bit[next] < target) {
                target -= bit[next];
                idx = next;
            }
        }
        return idx + 1; // 1-based index
    }

    private int highestPowerOfTwo(int x) {
        int p = 1;
        while ((p << 1) <= x) p <<= 1;
        return p;
    }

    public int size() { return n; }

    @Override
    public String toString() {
        return "FenwickTree{" +
                "n=" + n +
                ", bit=" + Arrays.toString(bit) +
                '}';
    }

    public static void main(String[] args) {
        int[] arr = {1, 2, 3, 4, 5};
        FenwickTree ft = new FenwickTree(arr);
        System.out.println("Initial: " + Arrays.toString(arr));
        System.out.println("prefixSum(3) -> " + ft.prefixSum(3)); // 1+2+3 = 6
        System.out.println("rangeSum(2,5) -> " + ft.rangeSum(2, 5)); // 2+3+4+5 = 14

        // Update: add +3 at index 4 (1-based)
        ft.update(4, 3);
        System.out.println("After update(4,+3), prefixSum(5) -> " + ft.prefixSum(5)); // 1+2+3+(4+3)+5 = 18
        System.out.println("rangeSum(4,4) -> " + ft.rangeSum(4, 4)); // 7

        // Find by prefix sum
        System.out.println("findByPrefixSum(6) -> index " + ft.findByPrefixSum(6)); // first index where sum>=6

        System.out.println("Ops: update/query O(log n); Space O(n)");
    }
}
