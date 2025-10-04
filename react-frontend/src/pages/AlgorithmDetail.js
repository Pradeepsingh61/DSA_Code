import React, { useState, useEffect } from 'react';
import { useParams, Link } from 'react-router-dom';
import { motion } from 'framer-motion';
import { Helmet } from 'react-helmet-async';
import { 
  ArrowLeft, 
  Clock, 
  HardDrive, 
  Github, 
  Copy,
  ExternalLink,
  Tag,
  User,
  Calendar,
  Loader
} from 'lucide-react';
import { useGitHub } from '../context/GitHubContext';
import CodeWindow from '../components/CodeWindow';
import toast from 'react-hot-toast';

const AlgorithmDetail = () => {
  const { id } = useParams();
  const [algorithm, setAlgorithm] = useState(null);
  const [code, setCode] = useState('');
  const [loading, setLoading] = useState(true);
  const { fetchFileContent, getFileUrl } = useGitHub();

  // Mock algorithm data - in real app, this would come from API
  const algorithmData = {
    'fenwick-tree': {
      id: 'fenwick-tree',
      name: 'Fenwick Tree (Binary Indexed Tree)',
      category: 'data-structures',
      language: 'Java',
      difficulty: 'Medium',
      description: 'A Fenwick Tree (Binary Indexed Tree) is a data structure that efficiently supports prefix sum queries and point updates on an array. It provides both operations in O(log n) time complexity, making it much more efficient than naive approaches.',
      timeComplexity: 'O(log n)',
      spaceComplexity: 'O(n)',
      path: 'Java/data_structures/trees/FenwickTree.java',
      tags: ['tree', 'range-queries', 'binary-indexed-tree', 'prefix-sum'],
      operations: ['update', 'query', 'prefixSum', 'set', 'get'],
      author: 'adarsh-priydarshi',
      lastUpdated: '2024-10-04',
      applications: [
        'Prefix sum calculations',
        'Range sum queries',
        'Frequency counting',
        'Inversion counting',
        '2D range sum queries'
      ],
      keyFeatures: [
        'Range sum queries in O(log n)',
        'Point updates in O(log n)',
        'Space complexity: O(n)',
        'Uses bit manipulation for efficient tree traversal'
      ]
    },
    'matrix-multiplication': {
      id: 'matrix-multiplication',
      name: 'Matrix Multiplication',
      category: 'mathematical',
      language: 'Java',
      difficulty: 'Medium',
      description: 'Efficient matrix multiplication algorithm with comprehensive error handling and input validation. Implements the standard algorithm for multiplying two matrices.',
      timeComplexity: 'O(m×n×p)',
      spaceComplexity: 'O(m×p)',
      path: 'Java/algorithms/matrix/MatrixMultiplication.java',
      tags: ['matrix', 'multiplication', 'mathematical', 'linear-algebra'],
      operations: ['multiply', 'validate', 'display'],
      author: 'contributor',
      lastUpdated: '2024-10-03',
      applications: [
        'Computer graphics transformations',
        'Machine learning computations',
        'Scientific computing',
        'Image processing',
        'Graph algorithms'
      ],
      keyFeatures: [
        'Input validation and error handling',
        'Interactive user interface',
        'Comprehensive test cases',
        'Memory efficient implementation'
      ]
    },
    'quick-sort': {
      id: 'quick-sort',
      name: 'Quick Sort',
      category: 'sorting',
      language: 'Java',
      difficulty: 'Medium',
      description: 'Quick Sort is a highly efficient divide-and-conquer sorting algorithm. It works by selecting a pivot element and partitioning the array around it, then recursively sorting the sub-arrays.',
      timeComplexity: 'O(n log n)',
      spaceComplexity: 'O(log n)',
      path: 'Java/algorithms/sorting/QuickSort.java',
      tags: ['sorting', 'divide-conquer', 'in-place', 'recursive'],
      operations: ['sort', 'partition', 'quickSelect'],
      author: 'contributor',
      lastUpdated: '2024-10-01',
      applications: [
        'General purpose sorting',
        'Database query optimization',
        'Selection algorithms (finding kth element)',
        'Competitive programming',
        'System sorting utilities'
      ],
      keyFeatures: [
        'Average O(n log n) time complexity',
        'In-place sorting algorithm',
        'Divide and conquer approach',
        'Efficient for large datasets',
        'Cache-friendly implementation'
      ]
    },
    'binary-search': {
      id: 'binary-search',
      name: 'Binary Search',
      category: 'searching',
      language: 'Java',
      difficulty: 'Easy',
      description: 'Binary Search is an efficient algorithm for finding an item from a sorted list of items. It works by repeatedly dividing the search interval in half.',
      timeComplexity: 'O(log n)',
      spaceComplexity: 'O(1)',
      path: 'Java/algorithms/BinarySearch.java',
      tags: ['searching', 'sorted-array', 'logarithmic', 'iterative'],
      operations: ['search', 'findFirst', 'findLast', 'findInsertPosition'],
      author: 'contributor',
      lastUpdated: '2024-09-28',
      applications: [
        'Searching in sorted arrays',
        'Finding insertion points',
        'Range queries',
        'Database indexing',
        'Library search functions'
      ],
      keyFeatures: [
        'Logarithmic time complexity',
        'Works only on sorted data',
        'Space efficient O(1)',
        'Simple implementation',
        'Foundation for many algorithms'
      ]
    },
    'dijkstra-algorithm': {
      id: 'dijkstra-algorithm',
      name: 'Dijkstra Algorithm',
      category: 'graph',
      language: 'Java',
      difficulty: 'Hard',
      description: 'Dijkstra\'s algorithm finds the shortest paths between nodes in a graph. It uses a priority queue to always process the closest unvisited vertex.',
      timeComplexity: 'O((V + E) log V)',
      spaceComplexity: 'O(V)',
      path: 'Java/algorithms/graph_algorithms/DijkstraAlgorithm.java',
      tags: ['graph', 'shortest-path', 'weighted', 'greedy'],
      operations: ['findShortestPath', 'relaxEdges', 'extractMin', 'updateDistance'],
      author: 'contributor',
      lastUpdated: '2024-09-25',
      applications: [
        'GPS navigation systems',
        'Network routing protocols',
        'Social network analysis',
        'Game pathfinding',
        'Flight connection systems'
      ],
      keyFeatures: [
        'Finds shortest path in weighted graphs',
        'Uses priority queue for efficiency',
        'Greedy algorithm approach',
        'Works with non-negative weights',
        'Optimal substructure property'
      ]
    },
    'a-star-search': {
      id: 'a-star-search',
      name: 'A* Search',
      category: 'graph',
      language: 'Java',
      difficulty: 'Hard',
      description: 'A* (A-star) is a graph traversal and path search algorithm that uses heuristics to find the optimal path. It combines the benefits of Dijkstra\'s algorithm and Greedy Best-First Search.',
      timeComplexity: 'O(b^d)',
      spaceComplexity: 'O(b^d)',
      path: 'Java/algorithms/graph_algorithms/AStarSearch.java',
      tags: ['graph', 'pathfinding', 'heuristic', 'ai', 'optimal'],
      operations: ['findPath', 'heuristic', 'reconstructPath', 'fScore', 'gScore'],
      author: 'contributor',
      lastUpdated: '2024-09-20',
      applications: [
        'Video game AI pathfinding',
        'Robotics navigation',
        'Route planning applications',
        'Puzzle solving algorithms',
        'AI search problems'
      ],
      keyFeatures: [
        'Optimal pathfinding with heuristics',
        'Combines Dijkstra and Greedy approaches',
        'Uses f(n) = g(n) + h(n) evaluation',
        'Admissible heuristic guarantees optimality',
        'Widely used in AI applications'
      ]
    },
    'merge-sort': {
      id: 'merge-sort',
      name: 'Merge Sort',
      category: 'sorting',
      language: 'Python',
      difficulty: 'Medium',
      description: 'Merge Sort is a stable, divide-and-conquer sorting algorithm that divides the array into halves, sorts them separately, and then merges them back together.',
      timeComplexity: 'O(n log n)',
      spaceComplexity: 'O(n)',
      path: 'Python/algorithms/sorting/merge_sort.py',
      tags: ['sorting', 'stable', 'divide-conquer', 'recursive'],
      operations: ['sort', 'merge', 'divide', 'conquer'],
      author: 'contributor',
      lastUpdated: '2024-09-15',
      applications: [
        'External sorting for large datasets',
        'Stable sorting requirements',
        'Parallel processing applications',
        'Merge operations in databases',
        'Version control systems'
      ],
      keyFeatures: [
        'Guaranteed O(n log n) performance',
        'Stable sorting algorithm',
        'Predictable performance',
        'Parallelizable algorithm',
        'Good for linked lists'
      ]
    },
    'heap-sort': {
      id: 'heap-sort',
      name: 'Heap Sort',
      category: 'sorting',
      language: 'C++',
      difficulty: 'Medium',
      description: 'Heap Sort is a comparison-based sorting algorithm that uses a binary heap data structure. It builds a max heap and repeatedly extracts the maximum element.',
      timeComplexity: 'O(n log n)',
      spaceComplexity: 'O(1)',
      path: 'CPP/algorithms/sorting/heap_sort.cpp',
      tags: ['sorting', 'heap', 'in-place', 'comparison-based'],
      operations: ['sort', 'heapify', 'buildHeap', 'extractMax'],
      author: 'contributor',
      lastUpdated: '2024-09-10',
      applications: [
        'Priority queue implementation',
        'Selection algorithms',
        'Memory-constrained environments',
        'Real-time systems',
        'Embedded systems programming'
      ],
      keyFeatures: [
        'In-place sorting algorithm',
        'Guaranteed O(n log n) performance',
        'Not stable but consistent',
        'Uses heap data structure',
        'Memory efficient'
      ]
    }
  };

  useEffect(() => {
    const loadAlgorithm = async () => {
      setLoading(true);
      try {
        const algoData = algorithmData[id];
        if (algoData) {
          setAlgorithm(algoData);
          
          // Fetch real code from GitHub
          const codeContent = await fetchFileContent(algoData.path);
          if (codeContent) {
            setCode(codeContent);
          } else {
            // Fallback code for demo
            setCode(getFallbackCode(id));
          }
        }
      } catch (error) {
        console.error('Error loading algorithm:', error);
        toast.error('Failed to load algorithm details');
      } finally {
        setLoading(false);
      }
    };

    loadAlgorithm();
  }, [id, fetchFileContent]);

  const getFallbackCode = (algorithmId) => {
    switch (algorithmId) {
      case 'fenwick-tree':
        return `/**
 * Fenwick Tree (Binary Indexed Tree) Implementation in Java
 * Time Complexity: O(log n) for all operations
 * Space Complexity: O(n)
 */
public class FenwickTree {
    private int[] tree;
    private int n;
    
    public FenwickTree(int size) {
        this.n = size;
        this.tree = new int[n + 1];
    }
    
    public void update(int index, int delta) {
        index++;
        while (index <= n) {
            tree[index] += delta;
            index += index & (-index);
        }
    }
    
    public int query(int left, int right) {
        if (left == 0) return prefixSum(right);
        return prefixSum(right) - prefixSum(left - 1);
    }
    
    private int prefixSum(int index) {
        index++;
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & (-index);
        }
        return sum;
    }
}`;

      case 'matrix-multiplication':
        return `/**
 * Matrix Multiplication Implementation in Java
 * Time Complexity: O(m×n×p)
 * Space Complexity: O(m×p)
 */
public class MatrixMultiplication {
    
    public static int[][] multiply(int[][] A, int[][] B) {
        int m = A.length;
        int n = A[0].length;
        int p = B[0].length;
        
        // Validate dimensions
        if (n != B.length) {
            throw new IllegalArgumentException("Invalid matrix dimensions");
        }
        
        int[][] result = new int[m][p];
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < p; j++) {
                for (int k = 0; k < n; k++) {
                    result[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        
        return result;
    }
    
    public static void displayMatrix(int[][] matrix) {
        for (int[] row : matrix) {
            for (int element : row) {
                System.out.print(element + " ");
            }
            System.out.println();
        }
    }
}`;

      case 'quick-sort':
        return `/**
 * Quick Sort Implementation in Java
 * Time Complexity: O(n log n) average, O(n²) worst
 * Space Complexity: O(log n)
 */
public class QuickSort {
    
    public static void quickSort(int[] arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
    
    private static int partition(int[] arr, int low, int high) {
        int pivot = arr[high];
        int i = (low - 1);
        
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap(arr, i, j);
            }
        }
        
        swap(arr, i + 1, high);
        return i + 1;
    }
    
    private static void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}`;

      case 'binary-search':
        return `/**
 * Binary Search Implementation in Java
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */
public class BinarySearch {
    
    public static int binarySearch(int[] arr, int target) {
        int left = 0;
        int right = arr.length - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) {
                return mid;
            }
            
            if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1; // Element not found
    }
    
    public static int findFirst(int[] arr, int target) {
        int result = -1;
        int left = 0, right = arr.length - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) {
                result = mid;
                right = mid - 1; // Continue searching left
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
}`;

      case 'dijkstra-algorithm':
        return `/**
 * Dijkstra's Algorithm Implementation in Java
 * Time Complexity: O((V + E) log V)
 * Space Complexity: O(V)
 */
import java.util.*;

public class DijkstraAlgorithm {
    
    static class Edge {
        int destination, weight;
        
        Edge(int destination, int weight) {
            this.destination = destination;
            this.weight = weight;
        }
    }
    
    public static int[] dijkstra(List<List<Edge>> graph, int source) {
        int V = graph.size();
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[source] = 0;
        
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> a[1] - b[1]);
        pq.offer(new int[]{source, 0});
        
        while (!pq.isEmpty()) {
            int[] current = pq.poll();
            int u = current[0];
            
            for (Edge edge : graph.get(u)) {
                int v = edge.destination;
                int weight = edge.weight;
                
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.offer(new int[]{v, dist[v]});
                }
            }
        }
        
        return dist;
    }
}`;

      case 'a-star-search':
        return `/**
 * A* Search Algorithm Implementation in Java
 * Time Complexity: O(b^d)
 * Space Complexity: O(b^d)
 */
import java.util.*;

public class AStarSearch {
    
    static class Node implements Comparable<Node> {
        int x, y, g, h, f;
        Node parent;
        
        Node(int x, int y, int g, int h, Node parent) {
            this.x = x;
            this.y = y;
            this.g = g;
            this.h = h;
            this.f = g + h;
            this.parent = parent;
        }
        
        @Override
        public int compareTo(Node other) {
            return this.f - other.f;
        }
    }
    
    static int heuristic(int x, int y, int targetX, int targetY) {
        return Math.abs(x - targetX) + Math.abs(y - targetY);
    }
    
    public static List<int[]> aStar(int[][] grid, int[] start, int[] target) {
        int rows = grid.length, cols = grid[0].length;
        boolean[][] visited = new boolean[rows][cols];
        PriorityQueue<Node> pq = new PriorityQueue<>();
        
        pq.add(new Node(start[0], start[1], 0, 
                       heuristic(start[0], start[1], target[0], target[1]), null));
        
        int[][] directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        
        while (!pq.isEmpty()) {
            Node current = pq.poll();
            
            if (visited[current.x][current.y]) continue;
            visited[current.x][current.y] = true;
            
            if (current.x == target[0] && current.y == target[1]) {
                List<int[]> path = new ArrayList<>();
                Node temp = current;
                while (temp != null) {
                    path.add(new int[]{temp.x, temp.y});
                    temp = temp.parent;
                }
                Collections.reverse(path);
                return path;
            }
            
            for (int[] dir : directions) {
                int nx = current.x + dir[0];
                int ny = current.y + dir[1];
                
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && 
                    grid[nx][ny] == 0 && !visited[nx][ny]) {
                    int gNew = current.g + 1;
                    int hNew = heuristic(nx, ny, target[0], target[1]);
                    pq.add(new Node(nx, ny, gNew, hNew, current));
                }
            }
        }
        
        return null; // No path found
    }
}`;

      case 'merge-sort':
        return `"""
Merge Sort Implementation in Python
Time Complexity: O(n log n)
Space Complexity: O(n)
"""

def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    
    return merge(left, right)

def merge(left, right):
    result = []
    i = j = 0
    
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            result.append(left[i])
            i += 1
        else:
            result.append(right[j])
            j += 1
    
    result.extend(left[i:])
    result.extend(right[j:])
    
    return result

# Example usage
if __name__ == "__main__":
    arr = [64, 34, 25, 12, 22, 11, 90]
    print("Original array:", arr)
    
    sorted_arr = merge_sort(arr)
    print("Sorted array:", sorted_arr)`;

      case 'heap-sort':
        return `/**
 * Heap Sort Implementation in C++
 * Time Complexity: O(n log n)
 * Space Complexity: O(1)
 */
#include <iostream>
#include <vector>
using namespace std;

class HeapSort {
public:
    static void heapSort(vector<int>& arr) {
        int n = arr.size();
        
        // Build max heap
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
        
        // Extract elements from heap one by one
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
    
private:
    static void heapify(vector<int>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
        
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
};

int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    
    cout << "Original array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    HeapSort::heapSort(arr);
    
    cout << "Sorted array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    return 0;
}`;

      default:
        return `// Algorithm implementation loading...
// This algorithm's code will be fetched from GitHub repository
// Please check back in a moment or visit the GitHub link above`;
    }
  };

  const getDifficultyColor = (difficulty) => {
    switch (difficulty?.toLowerCase()) {
      case 'easy': return 'var(--secondary-color)';
      case 'medium': return 'var(--accent-color)';
      case 'hard': return 'var(--danger-color)';
      default: return 'var(--text-secondary)';
    }
  };

  if (loading) {
    return (
      <div className="loading-container">
        <Loader className="spinner" size={32} />
        <p>Loading algorithm details...</p>
      </div>
    );
  }

  if (!algorithm) {
    return (
      <div className="not-found">
        <h2>Algorithm not found</h2>
        <Link to="/algorithms" className="btn btn-primary">
          <ArrowLeft size={16} />
          Back to Algorithms
        </Link>
      </div>
    );
  }

  return (
    <motion.div
      className="algorithm-detail"
      initial={{ opacity: 0 }}
      animate={{ opacity: 1 }}
      exit={{ opacity: 0 }}
    >
      <Helmet>
        <title>{algorithm.name} - DSA Code</title>
        <meta name="description" content={algorithm.description} />
      </Helmet>

      <div className="container">
        <motion.div
          className="breadcrumb"
          initial={{ opacity: 0, y: -20 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ duration: 0.5 }}
        >
          <Link to="/algorithms" className="breadcrumb-link">
            <ArrowLeft size={16} />
            Back to Algorithms
          </Link>
        </motion.div>

        <motion.div
          className="algorithm-header"
          initial={{ opacity: 0, y: 30 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ duration: 0.6 }}
        >
          <div className="header-content">
            <h1>{algorithm.name}</h1>
            <div className="header-badges">
              <span 
                className="difficulty-badge"
                style={{ 
                  backgroundColor: `${getDifficultyColor(algorithm.difficulty)}20`,
                  color: getDifficultyColor(algorithm.difficulty)
                }}
              >
                {algorithm.difficulty}
              </span>
              <span className="language-badge">{algorithm.language}</span>
              <span className="category-badge">{algorithm.category}</span>
            </div>
            <p className="algorithm-description">{algorithm.description}</p>
          </div>

          <div className="header-actions">
            <a
              href={getFileUrl(algorithm.path)}
              target="_blank"
              rel="noopener noreferrer"
              className="btn btn-primary"
            >
              <Github size={16} />
              View on GitHub
            </a>
          </div>
        </motion.div>

        <div className="algorithm-content">
          <div className="content-grid">
            <motion.div
              className="algorithm-info"
              initial={{ opacity: 0, x: -30 }}
              animate={{ opacity: 1, x: 0 }}
              transition={{ duration: 0.6, delay: 0.2 }}
            >
              <div className="info-section">
                <h3>Complexity Analysis</h3>
                <div className="complexity-grid">
                  <div className="complexity-item">
                    <Clock size={20} />
                    <div>
                      <strong>Time Complexity</strong>
                      <span>{algorithm.timeComplexity}</span>
                    </div>
                  </div>
                  <div className="complexity-item">
                    <HardDrive size={20} />
                    <div>
                      <strong>Space Complexity</strong>
                      <span>{algorithm.spaceComplexity}</span>
                    </div>
                  </div>
                </div>
              </div>

              {algorithm.keyFeatures && (
                <div className="info-section">
                  <h3>Key Features</h3>
                  <ul className="feature-list">
                    {algorithm.keyFeatures.map((feature, index) => (
                      <li key={index}>{feature}</li>
                    ))}
                  </ul>
                </div>
              )}

              {algorithm.applications && (
                <div className="info-section">
                  <h3>Applications</h3>
                  <ul className="application-list">
                    {algorithm.applications.map((app, index) => (
                      <li key={index}>{app}</li>
                    ))}
                  </ul>
                </div>
              )}

              {algorithm.operations && (
                <div className="info-section">
                  <h3>Operations</h3>
                  <div className="operations-grid">
                    {algorithm.operations.map((operation, index) => (
                      <span key={index} className="operation-tag">
                        {operation}
                      </span>
                    ))}
                  </div>
                </div>
              )}

              {algorithm.tags && (
                <div className="info-section">
                  <h3>Tags</h3>
                  <div className="tags-grid">
                    {algorithm.tags.map((tag, index) => (
                      <span key={index} className="tag">
                        <Tag size={12} />
                        {tag}
                      </span>
                    ))}
                  </div>
                </div>
              )}

              <div className="info-section">
                <h3>Metadata</h3>
                <div className="metadata">
                  <div className="metadata-item">
                    <User size={16} />
                    <span>Author: {algorithm.author}</span>
                  </div>
                  <div className="metadata-item">
                    <Calendar size={16} />
                    <span>Last Updated: {new Date(algorithm.lastUpdated).toLocaleDateString()}</span>
                  </div>
                </div>
              </div>
            </motion.div>

            <motion.div
              className="algorithm-code"
              initial={{ opacity: 0, x: 30 }}
              animate={{ opacity: 1, x: 0 }}
              transition={{ duration: 0.6, delay: 0.3 }}
            >
              <CodeWindow
                title={algorithm.path.split('/').pop()}
                language={algorithm.language.toLowerCase()}
                code={code}
                githubUrl={getFileUrl(algorithm.path)}
              />
            </motion.div>
          </div>
        </div>
      </div>

      <style jsx>{`
        .algorithm-detail {
          padding-top: 70px;
          min-height: 100vh;
        }

        .container {
          max-width: 1200px;
          margin: 0 auto;
          padding: 2rem;
        }

        .breadcrumb {
          margin-bottom: 2rem;
        }

        .breadcrumb-link {
          display: inline-flex;
          align-items: center;
          gap: 0.5rem;
          color: var(--text-secondary);
          text-decoration: none;
          transition: color var(--transition-fast);
        }

        .breadcrumb-link:hover {
          color: var(--primary-color);
        }

        .algorithm-header {
          display: flex;
          justify-content: space-between;
          align-items: flex-start;
          gap: 2rem;
          margin-bottom: 3rem;
          padding-bottom: 2rem;
          border-bottom: 1px solid var(--border-color);
        }

        .header-content {
          flex: 1;
        }

        .algorithm-header h1 {
          font-size: 2.5rem;
          font-weight: 700;
          margin-bottom: 1rem;
          color: var(--text-primary);
        }

        .header-badges {
          display: flex;
          gap: 0.75rem;
          margin-bottom: 1.5rem;
          flex-wrap: wrap;
        }

        .difficulty-badge,
        .language-badge,
        .category-badge {
          padding: 0.5rem 1rem;
          border-radius: var(--radius-md);
          font-size: 0.875rem;
          font-weight: 600;
          text-transform: capitalize;
        }

        .language-badge {
          background-color: rgba(99, 102, 241, 0.1);
          color: var(--primary-color);
        }

        .category-badge {
          background-color: var(--bg-tertiary);
          color: var(--text-secondary);
        }

        .algorithm-description {
          font-size: 1.125rem;
          line-height: 1.7;
          color: var(--text-secondary);
          margin: 0;
        }

        .content-grid {
          display: grid;
          grid-template-columns: 1fr 1fr;
          gap: 3rem;
        }

        .algorithm-info {
          display: flex;
          flex-direction: column;
          gap: 2rem;
        }

        .info-section {
          background-color: var(--bg-card);
          border: 1px solid var(--border-color);
          border-radius: var(--radius-lg);
          padding: 1.5rem;
        }

        .info-section h3 {
          font-size: 1.25rem;
          font-weight: 600;
          margin-bottom: 1rem;
          color: var(--text-primary);
        }

        .complexity-grid {
          display: flex;
          flex-direction: column;
          gap: 1rem;
        }

        .complexity-item {
          display: flex;
          align-items: center;
          gap: 1rem;
        }

        .complexity-item svg {
          color: var(--primary-color);
          flex-shrink: 0;
        }

        .complexity-item div {
          display: flex;
          flex-direction: column;
          gap: 0.25rem;
        }

        .complexity-item strong {
          font-weight: 600;
          color: var(--text-primary);
        }

        .complexity-item span {
          color: var(--text-secondary);
          font-family: var(--font-mono);
          font-size: 0.9rem;
        }

        .feature-list,
        .application-list {
          list-style: none;
          padding: 0;
          margin: 0;
        }

        .feature-list li,
        .application-list li {
          padding: 0.5rem 0;
          border-bottom: 1px solid var(--border-color);
          color: var(--text-secondary);
        }

        .feature-list li:last-child,
        .application-list li:last-child {
          border-bottom: none;
        }

        .operations-grid,
        .tags-grid {
          display: flex;
          flex-wrap: wrap;
          gap: 0.5rem;
        }

        .operation-tag {
          padding: 0.5rem 1rem;
          background-color: rgba(16, 185, 129, 0.1);
          color: var(--secondary-color);
          border-radius: var(--radius-md);
          font-size: 0.875rem;
          font-weight: 500;
        }

        .tag {
          display: flex;
          align-items: center;
          gap: 0.25rem;
          padding: 0.375rem 0.75rem;
          background-color: rgba(99, 102, 241, 0.1);
          color: var(--primary-color);
          border-radius: var(--radius-md);
          font-size: 0.8rem;
          font-weight: 500;
        }

        .metadata {
          display: flex;
          flex-direction: column;
          gap: 0.75rem;
        }

        .metadata-item {
          display: flex;
          align-items: center;
          gap: 0.5rem;
          color: var(--text-secondary);
          font-size: 0.9rem;
        }

        .metadata-item svg {
          color: var(--primary-color);
          flex-shrink: 0;
        }

        .loading-container,
        .not-found {
          display: flex;
          flex-direction: column;
          align-items: center;
          justify-content: center;
          min-height: 50vh;
          gap: 1rem;
          color: var(--text-secondary);
        }

        .spinner {
          animation: spin 1s linear infinite;
        }

        @keyframes spin {
          from { transform: rotate(0deg); }
          to { transform: rotate(360deg); }
        }

        @media (max-width: 1024px) {
          .content-grid {
            grid-template-columns: 1fr;
            gap: 2rem;
          }

          .algorithm-header {
            flex-direction: column;
            align-items: stretch;
          }
        }

        @media (max-width: 768px) {
          .container {
            padding: 1rem;
          }

          .algorithm-header h1 {
            font-size: 2rem;
          }

          .header-badges {
            gap: 0.5rem;
          }

          .complexity-grid {
            gap: 0.75rem;
          }

          .complexity-item {
            flex-direction: column;
            align-items: flex-start;
            gap: 0.5rem;
          }
        }
      `}</style>
    </motion.div>
  );
};

export default AlgorithmDetail;
