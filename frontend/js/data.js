// Data for DSA Code Frontend
const DSAData = {
    algorithms: [
        {
            name: 'Fenwick Tree',
            category: 'data-structures',
            language: 'Java',
            difficulty: 'Medium',
            description: 'Binary Indexed Tree for efficient range sum queries and point updates',
            timeComplexity: 'O(log n)',
            spaceComplexity: 'O(n)',
            path: 'Java/data_structures/trees/FenwickTree.java',
            tags: ['tree', 'range-queries', 'binary-indexed-tree'],
            operations: ['update', 'query', 'prefixSum', 'set', 'get']
        },
        {
            name: 'Matrix Multiplication',
            category: 'mathematical',
            language: 'Java',
            difficulty: 'Medium',
            description: 'Efficient matrix multiplication algorithm with comprehensive error handling',
            timeComplexity: 'O(m×n×p)',
            spaceComplexity: 'O(m×p)',
            path: 'Java/algorithms/matrix/MatrixMultiplication.java',
            tags: ['matrix', 'multiplication', 'mathematical'],
            operations: ['multiply', 'validate', 'display']
        },
        {
            name: 'Quick Sort',
            category: 'sorting',
            language: 'Java',
            difficulty: 'Medium',
            description: 'Efficient divide-and-conquer sorting algorithm',
            timeComplexity: 'O(n log n)',
            spaceComplexity: 'O(log n)',
            path: 'Java/algorithms/sorting/QuickSort.java',
            tags: ['sorting', 'divide-conquer', 'in-place'],
            operations: ['sort', 'partition', 'quickSelect']
        },
        {
            name: 'Binary Search',
            category: 'searching',
            language: 'Java',
            difficulty: 'Easy',
            description: 'Efficient search algorithm for sorted arrays',
            timeComplexity: 'O(log n)',
            spaceComplexity: 'O(1)',
            path: 'Java/algorithms/BinarySearch.java',
            tags: ['searching', 'sorted-array', 'logarithmic'],
            operations: ['search', 'findFirst', 'findLast']
        },
        {
            name: 'Dijkstra Algorithm',
            category: 'graph',
            language: 'Java',
            difficulty: 'Hard',
            description: 'Shortest path algorithm for weighted graphs',
            timeComplexity: 'O((V + E) log V)',
            spaceComplexity: 'O(V)',
            path: 'Java/algorithms/graph_algorithms/DijkstraAlgorithm.java',
            tags: ['graph', 'shortest-path', 'weighted'],
            operations: ['findShortestPath', 'relaxEdges', 'extractMin']
        },
        {
            name: 'A* Search',
            category: 'graph',
            language: 'Java',
            difficulty: 'Hard',
            description: 'Heuristic pathfinding algorithm for optimal path finding',
            timeComplexity: 'O(b^d)',
            spaceComplexity: 'O(b^d)',
            path: 'Java/algorithms/graph_algorithms/AStarSearch.java',
            tags: ['graph', 'pathfinding', 'heuristic', 'ai'],
            operations: ['findPath', 'heuristic', 'reconstructPath']
        },
        {
            name: 'Merge Sort',
            category: 'sorting',
            language: 'Java',
            difficulty: 'Medium',
            description: 'Stable divide-and-conquer sorting algorithm',
            timeComplexity: 'O(n log n)',
            spaceComplexity: 'O(n)',
            path: 'Java/algorithms/sorting/MergeSort.java',
            tags: ['sorting', 'stable', 'divide-conquer'],
            operations: ['sort', 'merge', 'divide']
        },
        {
            name: 'Heap Sort',
            category: 'sorting',
            language: 'Java',
            difficulty: 'Medium',
            description: 'In-place sorting algorithm using binary heap',
            timeComplexity: 'O(n log n)',
            spaceComplexity: 'O(1)',
            path: 'Java/algorithms/sorting/HeapSort.java',
            tags: ['sorting', 'heap', 'in-place'],
            operations: ['sort', 'heapify', 'buildHeap']
        },
        {
            name: 'Floyd Warshall',
            category: 'graph',
            language: 'Java',
            difficulty: 'Hard',
            description: 'All-pairs shortest path algorithm',
            timeComplexity: 'O(V³)',
            spaceComplexity: 'O(V²)',
            path: 'Java/algorithms/graph_algorithms/FloydWarshall.java',
            tags: ['graph', 'shortest-path', 'all-pairs'],
            operations: ['findAllPaths', 'updateDistances', 'detectNegativeCycles']
        },
        {
            name: 'Bubble Sort',
            category: 'sorting',
            language: 'Java',
            difficulty: 'Easy',
            description: 'Simple comparison-based sorting algorithm',
            timeComplexity: 'O(n²)',
            spaceComplexity: 'O(1)',
            path: 'Java/algorithms/sorting/BubbleSort.java',
            tags: ['sorting', 'comparison', 'stable'],
            operations: ['sort', 'swap', 'optimize']
        }
    ],
    
    dataStructures: [
        {
            name: 'Fenwick Tree',
            language: 'Java',
            difficulty: 'Medium',
            description: 'Binary Indexed Tree for efficient range sum queries and point updates',
            operations: ['update', 'query', 'prefixSum', 'set', 'get'],
            path: 'Java/data_structures/trees/FenwickTree.java',
            timeComplexity: {
                insert: 'O(log n)',
                search: 'O(log n)',
                delete: 'O(log n)',
                update: 'O(log n)'
            },
            spaceComplexity: 'O(n)',
            tags: ['tree', 'range-queries', 'binary-indexed']
        },
        {
            name: 'Trie',
            language: 'Java',
            difficulty: 'Medium',
            description: 'Prefix tree for efficient string operations and autocomplete',
            operations: ['insert', 'search', 'startsWith', 'delete'],
            path: 'Java/data_structures/trees/Trie.java',
            timeComplexity: {
                insert: 'O(m)',
                search: 'O(m)',
                delete: 'O(m)',
                startsWith: 'O(m)'
            },
            spaceComplexity: 'O(ALPHABET_SIZE * N * M)',
            tags: ['tree', 'string', 'prefix', 'autocomplete']
        },
        {
            name: 'Binary Search Tree',
            language: 'Java',
            difficulty: 'Medium',
            description: 'Self-organizing binary tree for efficient searching',
            operations: ['insert', 'search', 'delete', 'inorder', 'preorder', 'postorder'],
            path: 'Java/data_structures/trees/BinarySearchTree.java',
            timeComplexity: {
                insert: 'O(log n)',
                search: 'O(log n)',
                delete: 'O(log n)'
            },
            spaceComplexity: 'O(n)',
            tags: ['tree', 'binary', 'search', 'ordered']
        },
        {
            name: 'Hash Table',
            language: 'Java',
            difficulty: 'Medium',
            description: 'Key-value data structure with constant time operations',
            operations: ['put', 'get', 'remove', 'containsKey', 'resize'],
            path: 'Java/data_structures/hash/HashTable.java',
            timeComplexity: {
                insert: 'O(1)',
                search: 'O(1)',
                delete: 'O(1)'
            },
            spaceComplexity: 'O(n)',
            tags: ['hash', 'key-value', 'constant-time']
        },
        {
            name: 'Linked List',
            language: 'Java',
            difficulty: 'Easy',
            description: 'Linear data structure with dynamic size',
            operations: ['add', 'remove', 'find', 'size', 'isEmpty'],
            path: 'Java/data_structures/linear/LinkedList.java',
            timeComplexity: {
                insert: 'O(1)',
                search: 'O(n)',
                delete: 'O(1)'
            },
            spaceComplexity: 'O(n)',
            tags: ['linear', 'dynamic', 'pointer-based']
        },
        {
            name: 'Stack',
            language: 'Java',
            difficulty: 'Easy',
            description: 'LIFO (Last In First Out) data structure',
            operations: ['push', 'pop', 'peek', 'isEmpty', 'size'],
            path: 'Java/data_structures/linear/Stack.java',
            timeComplexity: {
                insert: 'O(1)',
                delete: 'O(1)',
                search: 'O(n)'
            },
            spaceComplexity: 'O(n)',
            tags: ['linear', 'lifo', 'stack-operations']
        },
        {
            name: 'Queue',
            language: 'Java',
            difficulty: 'Easy',
            description: 'FIFO (First In First Out) data structure',
            operations: ['enqueue', 'dequeue', 'front', 'isEmpty', 'size'],
            path: 'Java/data_structures/linear/Queue.java',
            timeComplexity: {
                insert: 'O(1)',
                delete: 'O(1)',
                search: 'O(n)'
            },
            spaceComplexity: 'O(n)',
            tags: ['linear', 'fifo', 'queue-operations']
        },
        {
            name: 'Priority Queue',
            language: 'Java',
            difficulty: 'Medium',
            description: 'Queue with priority-based ordering using heap',
            operations: ['insert', 'extractMax', 'peek', 'increaseKey', 'isEmpty'],
            path: 'Java/data_structures/heap/PriorityQueue.java',
            timeComplexity: {
                insert: 'O(log n)',
                delete: 'O(log n)',
                search: 'O(n)'
            },
            spaceComplexity: 'O(n)',
            tags: ['heap', 'priority', 'queue']
        }
    ],
    
    languages: [
        {
            name: 'Java',
            icon: 'fab fa-java',
            description: 'Object-oriented programming with strong typing and platform independence',
            implementations: 250,
            color: '#f89820',
            features: ['Object-Oriented', 'Platform Independent', 'Strong Typing', 'Memory Management'],
            path: 'Java/'
        },
        {
            name: 'Python',
            icon: 'fab fa-python',
            description: 'Simple, readable, and powerful programming language',
            implementations: 180,
            color: '#3776ab',
            features: ['Easy Syntax', 'Dynamic Typing', 'Rich Libraries', 'Interpreted'],
            path: 'Python/'
        },
        {
            name: 'C++',
            icon: 'fas fa-code',
            description: 'High-performance system programming with object-oriented features',
            implementations: 320,
            color: '#00599c',
            features: ['High Performance', 'System Programming', 'Object-Oriented', 'Manual Memory Management'],
            path: 'CPP/'
        },
        {
            name: 'C',
            icon: 'fas fa-code',
            description: 'Low-level programming language for system development',
            implementations: 80,
            color: '#a8b9cc',
            features: ['Low Level', 'System Programming', 'Procedural', 'Minimal Runtime'],
            path: 'C/'
        },
        {
            name: 'Go',
            icon: 'fab fa-golang',
            description: 'Modern, concurrent programming language by Google',
            implementations: 25,
            color: '#00add8',
            features: ['Concurrent', 'Fast Compilation', 'Garbage Collection', 'Simple Syntax'],
            path: 'go/'
        },
        {
            name: 'JavaScript',
            icon: 'fab fa-js-square',
            description: 'Dynamic programming language for web development',
            implementations: 40,
            color: '#f7df1e',
            features: ['Dynamic', 'Event-Driven', 'Prototype-Based', 'First-Class Functions'],
            path: 'JavaScript/'
        }
    ],
    
    categories: [
        {
            name: 'Sorting',
            icon: 'fas fa-sort',
            description: 'Algorithms for arranging data in order',
            count: 15,
            algorithms: ['Quick Sort', 'Merge Sort', 'Heap Sort', 'Bubble Sort', 'Selection Sort']
        },
        {
            name: 'Searching',
            icon: 'fas fa-search',
            description: 'Algorithms for finding specific elements',
            count: 8,
            algorithms: ['Binary Search', 'Linear Search', 'Interpolation Search']
        },
        {
            name: 'Graph Algorithms',
            icon: 'fas fa-project-diagram',
            description: 'Algorithms for graph traversal and analysis',
            count: 12,
            algorithms: ['Dijkstra', 'A* Search', 'BFS', 'DFS', 'Floyd Warshall']
        },
        {
            name: 'Dynamic Programming',
            icon: 'fas fa-layer-group',
            description: 'Optimization technique using overlapping subproblems',
            count: 20,
            algorithms: ['Fibonacci', 'Knapsack', 'LCS', 'Edit Distance']
        },
        {
            name: 'Greedy Algorithms',
            icon: 'fas fa-coins',
            description: 'Algorithms making locally optimal choices',
            count: 10,
            algorithms: ['Huffman Coding', 'Activity Selection', 'Fractional Knapsack']
        },
        {
            name: 'Mathematical',
            icon: 'fas fa-calculator',
            description: 'Mathematical algorithms and computations',
            count: 18,
            algorithms: ['Matrix Multiplication', 'GCD', 'Prime Numbers', 'Factorization']
        }
    ],
    
    stats: {
        totalAlgorithms: 500,
        totalDataStructures: 100,
        totalLanguages: 6,
        totalContributors: 1000,
        githubStars: 2500,
        githubForks: 500
    },
    
    recentUpdates: [
        {
            type: 'algorithm',
            name: 'Fenwick Tree',
            language: 'Java',
            date: '2024-10-04',
            author: 'adarsh-priydarshi'
        },
        {
            type: 'algorithm',
            name: 'Matrix Multiplication',
            language: 'Java',
            date: '2024-10-03',
            author: 'contributor'
        },
        {
            type: 'data-structure',
            name: 'Trie',
            language: 'Python',
            date: '2024-10-02',
            author: 'contributor'
        }
    ]
};

// Export for use in other files
if (typeof module !== 'undefined' && module.exports) {
    module.exports = DSAData;
}
