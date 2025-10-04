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
    if (algorithmId === 'fenwick-tree') {
      return `/**
 * Fenwick Tree (Binary Indexed Tree) Implementation in Java
 * 
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
    }
    return '// Code loading...';
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
