import java.util.Arrays;

/**
 * Data Structure: Disjoint Set Union (Union-Find)
 * Description: Maintains a collection of disjoint sets with near O(1) amortized
 *              operations using path compression (find) and union by rank.
 *
 * Operations:
 *  - find(x): returns representative (root) of the set containing x
 *  - union(x, y): merges the sets containing x and y
 *  - connected(x, y): true if x and y are in the same set
 *
 * Time Complexity: Amortized ~O(1) per operation (inverse Ackermann)
 * Space Complexity: O(n)
 */
public class DisjointSetUnion {
    private final int[] parent;
    private final int[] rank;

    /**
     * Constructs a DSU for elements 0..n-1, each in its own set.
     * @param n number of elements
     * @throws IllegalArgumentException if n < 0
     */
    public DisjointSetUnion(int n) {
        if (n < 0) throw new IllegalArgumentException("n must be non-negative");
        this.parent = new int[n];
        this.rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    /**
     * Finds the representative of x with path compression.
     */
    public int find(int x) {
        if (x < 0 || x >= parent.length) throw new IndexOutOfBoundsException("index out of bounds: " + x);
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    /**
     * Unions the sets containing x and y using union by rank.
     * @return true if a merge happened, false if already in same set
     */
    public boolean union(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return false;
        if (rank[rx] < rank[ry]) {
            parent[rx] = ry;
        } else if (rank[rx] > rank[ry]) {
            parent[ry] = rx;
        } else {
            parent[ry] = rx;
            rank[rx]++;
        }
        return true;
    }

    /**
     * Checks if x and y belong to the same set.
     */
    public boolean connected(int x, int y) {
        return find(x) == find(y);
    }

    /**
     * Returns the number of elements managed by this DSU.
     */
    public int size() {
        return parent.length;
    }

    @Override
    public String toString() {
        // Show parent array for debugging
        return "parent=" + Arrays.toString(parent) + ", rank=" + Arrays.toString(rank);
    }

    public static void main(String[] args) {
        // Example usage
        DisjointSetUnion dsu = new DisjointSetUnion(10);
        System.out.println("Initial: " + dsu);

        dsu.union(0, 1);
        dsu.union(2, 3);
        dsu.union(3, 4);
        dsu.union(1, 2); // merges {0,1} with {2,3,4}
        dsu.union(5, 6);

        System.out.println("After unions: " + dsu);
        System.out.println("connected(0,4) -> " + dsu.connected(0, 4)); // true
        System.out.println("connected(0,6) -> " + dsu.connected(0, 6)); // false

        // Path compression check
        System.out.println("find(4) root -> " + dsu.find(4));
        System.out.println("Final: " + dsu);

        System.out.println("Ops: find/union amortized ~O(1); Space O(n)");
    }
}
