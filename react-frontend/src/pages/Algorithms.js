import React, { useState, useEffect } from 'react';
import { Link } from 'react-router-dom';
import { motion } from 'framer-motion';
import { Helmet } from 'react-helmet-async';
import { 
  Search, 
  Filter, 
  Clock, 
  HardDrive, 
  Code, 
  ExternalLink,
  Brain,
  Loader
} from 'lucide-react';
import { useGitHub } from '../context/GitHubContext';
import AlgorithmCard from '../components/AlgorithmCard';

const Algorithms = () => {
  const [algorithms, setAlgorithms] = useState([]);
  const [filteredAlgorithms, setFilteredAlgorithms] = useState([]);
  const [searchTerm, setSearchTerm] = useState('');
  const [selectedCategory, setSelectedCategory] = useState('all');
  const [selectedLanguage, setSelectedLanguage] = useState('all');
  const [loading, setLoading] = useState(true);

  const { fetchDirectoryContents, getFileUrl } = useGitHub();

  const categories = [
    { id: 'all', name: 'All Categories', count: 0 },
    { id: 'sorting', name: 'Sorting', count: 0 },
    { id: 'searching', name: 'Searching', count: 0 },
    { id: 'graph', name: 'Graph Algorithms', count: 0 },
    { id: 'dynamic', name: 'Dynamic Programming', count: 0 },
    { id: 'greedy', name: 'Greedy', count: 0 },
    { id: 'mathematical', name: 'Mathematical', count: 0 },
    { id: 'string', name: 'String Algorithms', count: 0 }
  ];

  const languages = [
    { id: 'all', name: 'All Languages' },
    { id: 'java', name: 'Java' },
    { id: 'python', name: 'Python' },
    { id: 'cpp', name: 'C++' },
    { id: 'c', name: 'C' },
    { id: 'javascript', name: 'JavaScript' },
    { id: 'go', name: 'Go' }
  ];

  // Real algorithm data with GitHub integration
  const algorithmData = [
    {
      id: 'fenwick-tree',
      name: 'Fenwick Tree (Binary Indexed Tree)',
      category: 'data-structures',
      language: 'Java',
      difficulty: 'Medium',
      description: 'Binary Indexed Tree for efficient range sum queries and point updates',
      timeComplexity: 'O(log n)',
      spaceComplexity: 'O(n)',
      path: 'Java/data_structures/trees/FenwickTree.java',
      tags: ['tree', 'range-queries', 'binary-indexed-tree'],
      operations: ['update', 'query', 'prefixSum', 'set', 'get'],
      author: 'adarsh-priydarshi',
      lastUpdated: '2024-10-04'
    },
    {
      id: 'matrix-multiplication',
      name: 'Matrix Multiplication',
      category: 'mathematical',
      language: 'Java',
      difficulty: 'Medium',
      description: 'Efficient matrix multiplication algorithm with comprehensive error handling',
      timeComplexity: 'O(m×n×p)',
      spaceComplexity: 'O(m×p)',
      path: 'Java/algorithms/matrix/MatrixMultiplication.java',
      tags: ['matrix', 'multiplication', 'mathematical'],
      operations: ['multiply', 'validate', 'display'],
      author: 'contributor',
      lastUpdated: '2024-10-03'
    },
    {
      id: 'quick-sort',
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
      id: 'binary-search',
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
      id: 'dijkstra-algorithm',
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
      id: 'a-star-search',
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
      id: 'merge-sort',
      name: 'Merge Sort',
      category: 'sorting',
      language: 'Python',
      difficulty: 'Medium',
      description: 'Stable divide-and-conquer sorting algorithm',
      timeComplexity: 'O(n log n)',
      spaceComplexity: 'O(n)',
      path: 'Python/algorithms/sorting/merge_sort.py',
      tags: ['sorting', 'stable', 'divide-conquer'],
      operations: ['sort', 'merge', 'divide']
    },
    {
      id: 'heap-sort',
      name: 'Heap Sort',
      category: 'sorting',
      language: 'C++',
      difficulty: 'Medium',
      description: 'In-place sorting algorithm using binary heap',
      timeComplexity: 'O(n log n)',
      spaceComplexity: 'O(1)',
      path: 'CPP/algorithms/sorting/heap_sort.cpp',
      tags: ['sorting', 'heap', 'in-place'],
      operations: ['sort', 'heapify', 'buildHeap']
    }
  ];

  useEffect(() => {
    const loadAlgorithms = async () => {
      setLoading(true);
      try {
        // In a real implementation, you would fetch from GitHub API
        // For now, we'll use the static data with GitHub URLs
        const algorithmsWithUrls = algorithmData.map(algo => ({
          ...algo,
          githubUrl: getFileUrl(algo.path)
        }));
        
        setAlgorithms(algorithmsWithUrls);
        setFilteredAlgorithms(algorithmsWithUrls);
      } catch (error) {
        console.error('Error loading algorithms:', error);
      } finally {
        setLoading(false);
      }
    };

    loadAlgorithms();
  }, [getFileUrl]);

  useEffect(() => {
    let filtered = algorithms;

    // Filter by search term
    if (searchTerm) {
      filtered = filtered.filter(algo =>
        algo.name.toLowerCase().includes(searchTerm.toLowerCase()) ||
        algo.description.toLowerCase().includes(searchTerm.toLowerCase()) ||
        algo.tags.some(tag => tag.toLowerCase().includes(searchTerm.toLowerCase()))
      );
    }

    // Filter by category
    if (selectedCategory !== 'all') {
      filtered = filtered.filter(algo => algo.category === selectedCategory);
    }

    // Filter by language
    if (selectedLanguage !== 'all') {
      filtered = filtered.filter(algo => 
        algo.language.toLowerCase() === selectedLanguage.toLowerCase()
      );
    }

    setFilteredAlgorithms(filtered);
  }, [algorithms, searchTerm, selectedCategory, selectedLanguage]);

  const getDifficultyColor = (difficulty) => {
    switch (difficulty.toLowerCase()) {
      case 'easy': return 'var(--secondary-color)';
      case 'medium': return 'var(--accent-color)';
      case 'hard': return 'var(--danger-color)';
      default: return 'var(--text-secondary)';
    }
  };

  return (
    <motion.div
      className="algorithms-page"
      initial={{ opacity: 0 }}
      animate={{ opacity: 1 }}
      exit={{ opacity: 0 }}
    >
      <Helmet>
        <title>Algorithms - DSA Code</title>
        <meta name="description" content="Explore our comprehensive collection of algorithms across different categories including sorting, searching, graph algorithms, and more." />
      </Helmet>

      <div className="page-header">
        <div className="container">
          <motion.div
            className="header-content"
            initial={{ opacity: 0, y: 30 }}
            animate={{ opacity: 1, y: 0 }}
            transition={{ duration: 0.6 }}
          >
            <div className="header-icon">
              <Brain size={48} />
            </div>
            <h1>Algorithms</h1>
            <p>Explore our comprehensive collection of algorithms across different categories</p>
          </motion.div>
        </div>
      </div>

      <div className="page-content">
        <div className="container">
          {/* Search and Filters */}
          <motion.div
            className="search-filters"
            initial={{ opacity: 0, y: 20 }}
            animate={{ opacity: 1, y: 0 }}
            transition={{ duration: 0.6, delay: 0.2 }}
          >
            <div className="search-box">
              <Search size={20} />
              <input
                type="text"
                placeholder="Search algorithms..."
                value={searchTerm}
                onChange={(e) => setSearchTerm(e.target.value)}
              />
            </div>

            <div className="filters">
              <div className="filter-group">
                <label>Category</label>
                <select
                  value={selectedCategory}
                  onChange={(e) => setSelectedCategory(e.target.value)}
                >
                  {categories.map(category => (
                    <option key={category.id} value={category.id}>
                      {category.name}
                    </option>
                  ))}
                </select>
              </div>

              <div className="filter-group">
                <label>Language</label>
                <select
                  value={selectedLanguage}
                  onChange={(e) => setSelectedLanguage(e.target.value)}
                >
                  {languages.map(language => (
                    <option key={language.id} value={language.id}>
                      {language.name}
                    </option>
                  ))}
                </select>
              </div>
            </div>
          </motion.div>

          {/* Results */}
          <motion.div
            className="results-header"
            initial={{ opacity: 0 }}
            animate={{ opacity: 1 }}
            transition={{ duration: 0.6, delay: 0.3 }}
          >
            <p>
              {loading ? 'Loading...' : `${filteredAlgorithms.length} algorithms found`}
            </p>
          </motion.div>

          {/* Algorithms Grid */}
          {loading ? (
            <div className="loading-container">
              <Loader className="spinner" size={32} />
              <p>Loading algorithms...</p>
            </div>
          ) : (
            <motion.div
              className="algorithms-grid"
              initial={{ opacity: 0 }}
              animate={{ opacity: 1 }}
              transition={{ duration: 0.6, delay: 0.4 }}
            >
              {filteredAlgorithms.map((algorithm, index) => (
                <motion.div
                  key={algorithm.id}
                  initial={{ opacity: 0, y: 30 }}
                  animate={{ opacity: 1, y: 0 }}
                  transition={{ duration: 0.6, delay: index * 0.1 }}
                >
                  <AlgorithmCard algorithm={algorithm} />
                </motion.div>
              ))}
            </motion.div>
          )}

          {!loading && filteredAlgorithms.length === 0 && (
            <motion.div
              className="no-results"
              initial={{ opacity: 0 }}
              animate={{ opacity: 1 }}
              transition={{ duration: 0.6 }}
            >
              <Brain size={64} />
              <h3>No algorithms found</h3>
              <p>Try adjusting your search criteria or filters</p>
            </motion.div>
          )}
        </div>
      </div>

      <style jsx>{`
        .algorithms-page {
          padding-top: 70px;
          min-height: 100vh;
        }

        .page-header {
          background: linear-gradient(135deg, var(--primary-color), var(--secondary-color));
          color: white;
          padding: 4rem 0;
          text-align: center;
        }

        .header-content {
          display: flex;
          flex-direction: column;
          align-items: center;
          gap: 1rem;
        }

        .header-icon {
          opacity: 0.9;
        }

        .header-content h1 {
          font-size: 3rem;
          font-weight: 700;
          margin: 0;
        }

        .header-content p {
          font-size: 1.25rem;
          opacity: 0.9;
          max-width: 600px;
          margin: 0;
        }

        .page-content {
          padding: 4rem 0;
        }

        .search-filters {
          background-color: var(--bg-card);
          border: 1px solid var(--border-color);
          border-radius: var(--radius-xl);
          padding: 2rem;
          margin-bottom: 3rem;
          box-shadow: var(--shadow-sm);
        }

        .search-box {
          position: relative;
          margin-bottom: 2rem;
        }

        .search-box svg {
          position: absolute;
          left: 1rem;
          top: 50%;
          transform: translateY(-50%);
          color: var(--text-muted);
        }

        .search-box input {
          width: 100%;
          padding: 1rem 1rem 1rem 3rem;
          border: 2px solid var(--border-color);
          border-radius: var(--radius-lg);
          font-size: 1rem;
          background-color: var(--bg-primary);
          color: var(--text-primary);
          transition: all var(--transition-fast);
        }

        .search-box input:focus {
          outline: none;
          border-color: var(--primary-color);
          box-shadow: 0 0 0 3px rgba(99, 102, 241, 0.1);
        }

        .filters {
          display: flex;
          gap: 2rem;
          flex-wrap: wrap;
        }

        .filter-group {
          display: flex;
          flex-direction: column;
          gap: 0.5rem;
          min-width: 200px;
        }

        .filter-group label {
          font-weight: 500;
          color: var(--text-secondary);
          font-size: 0.9rem;
        }

        .filter-group select {
          padding: 0.75rem;
          border: 2px solid var(--border-color);
          border-radius: var(--radius-md);
          background-color: var(--bg-primary);
          color: var(--text-primary);
          font-size: 0.9rem;
          transition: all var(--transition-fast);
        }

        .filter-group select:focus {
          outline: none;
          border-color: var(--primary-color);
        }

        .results-header {
          margin-bottom: 2rem;
        }

        .results-header p {
          color: var(--text-secondary);
          font-size: 1rem;
        }

        .algorithms-grid {
          display: grid;
          grid-template-columns: repeat(auto-fill, minmax(350px, 1fr));
          gap: 2rem;
        }

        .loading-container {
          display: flex;
          flex-direction: column;
          align-items: center;
          gap: 1rem;
          padding: 4rem 0;
          color: var(--text-secondary);
        }

        .spinner {
          animation: spin 1s linear infinite;
        }

        @keyframes spin {
          from { transform: rotate(0deg); }
          to { transform: rotate(360deg); }
        }

        .no-results {
          display: flex;
          flex-direction: column;
          align-items: center;
          gap: 1rem;
          padding: 4rem 0;
          text-align: center;
          color: var(--text-secondary);
        }

        .no-results h3 {
          font-size: 1.5rem;
          color: var(--text-primary);
        }

        @media (max-width: 768px) {
          .header-content h1 {
            font-size: 2rem;
          }

          .header-content p {
            font-size: 1rem;
          }

          .search-filters {
            padding: 1.5rem;
          }

          .filters {
            flex-direction: column;
            gap: 1rem;
          }

          .filter-group {
            min-width: auto;
          }

          .algorithms-grid {
            grid-template-columns: 1fr;
            gap: 1.5rem;
          }
        }
      `}</style>
    </motion.div>
  );
};

export default Algorithms;
