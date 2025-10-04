import React from 'react';
import { Link } from 'react-router-dom';
import { motion } from 'framer-motion';
import { 
  Clock, 
  HardDrive, 
  Code, 
  ExternalLink, 
  Eye,
  Tag
} from 'lucide-react';

const AlgorithmCard = ({ algorithm }) => {
  const getDifficultyColor = (difficulty) => {
    switch (difficulty.toLowerCase()) {
      case 'easy': return 'var(--secondary-color)';
      case 'medium': return 'var(--accent-color)';
      case 'hard': return 'var(--danger-color)';
      default: return 'var(--text-secondary)';
    }
  };

  const getLanguageColor = (language) => {
    switch (language.toLowerCase()) {
      case 'java': return '#f89820';
      case 'python': return '#3776ab';
      case 'javascript': return '#f7df1e';
      case 'c++': return '#00599c';
      case 'c': return '#a8b9cc';
      case 'go': return '#00add8';
      default: return 'var(--primary-color)';
    }
  };

  return (
    <motion.div
      className="algorithm-card"
      whileHover={{ y: -5 }}
      transition={{ duration: 0.2 }}
    >
      <div className="card-header">
        <div className="card-title-section">
          <h3 className="card-title">{algorithm.name}</h3>
          <div className="card-badges">
            <span 
              className="difficulty-badge"
              style={{ 
                backgroundColor: `${getDifficultyColor(algorithm.difficulty)}20`,
                color: getDifficultyColor(algorithm.difficulty)
              }}
            >
              {algorithm.difficulty}
            </span>
            <span 
              className="language-badge"
              style={{ 
                backgroundColor: `${getLanguageColor(algorithm.language)}20`,
                color: getLanguageColor(algorithm.language)
              }}
            >
              {algorithm.language}
            </span>
          </div>
        </div>
      </div>

      <div className="card-content">
        <p className="card-description">{algorithm.description}</p>

        <div className="complexity-info">
          <div className="complexity-item">
            <Clock size={16} />
            <span>Time: {algorithm.timeComplexity}</span>
          </div>
          <div className="complexity-item">
            <HardDrive size={16} />
            <span>Space: {algorithm.spaceComplexity}</span>
          </div>
        </div>

        {algorithm.tags && algorithm.tags.length > 0 && (
          <div className="tags-section">
            <Tag size={14} />
            <div className="tags">
              {algorithm.tags.slice(0, 3).map((tag, index) => (
                <span key={index} className="tag">
                  {tag}
                </span>
              ))}
              {algorithm.tags.length > 3 && (
                <span className="tag more">+{algorithm.tags.length - 3}</span>
              )}
            </div>
          </div>
        )}

        {algorithm.operations && algorithm.operations.length > 0 && (
          <div className="operations-section">
            <h4>Operations:</h4>
            <div className="operations">
              {algorithm.operations.slice(0, 4).map((operation, index) => (
                <span key={index} className="operation">
                  {operation}
                </span>
              ))}
              {algorithm.operations.length > 4 && (
                <span className="operation more">+{algorithm.operations.length - 4}</span>
              )}
            </div>
          </div>
        )}
      </div>

      <div className="card-actions">
        <Link 
          to={`/algorithms/${algorithm.id}`}
          className="btn btn-primary btn-sm"
        >
          <Eye size={16} />
          View Details
        </Link>
        
        {algorithm.githubUrl && (
          <a
            href={algorithm.githubUrl}
            target="_blank"
            rel="noopener noreferrer"
            className="btn btn-secondary btn-sm"
          >
            <ExternalLink size={16} />
            GitHub
          </a>
        )}
      </div>

      {algorithm.author && (
        <div className="card-footer">
          <div className="author-info">
            <Code size={14} />
            <span>by {algorithm.author}</span>
          </div>
          {algorithm.lastUpdated && (
            <div className="update-info">
              <span>{new Date(algorithm.lastUpdated).toLocaleDateString()}</span>
            </div>
          )}
        </div>
      )}

      <style jsx>{`
        .algorithm-card {
          background-color: var(--bg-card);
          border: 1px solid var(--border-color);
          border-radius: var(--radius-xl);
          padding: 1.5rem;
          box-shadow: var(--shadow-sm);
          transition: all var(--transition-normal);
          height: 100%;
          display: flex;
          flex-direction: column;
        }

        .algorithm-card:hover {
          box-shadow: var(--shadow-lg);
          border-color: var(--primary-color);
        }

        .card-header {
          margin-bottom: 1rem;
        }

        .card-title-section {
          display: flex;
          flex-direction: column;
          gap: 0.75rem;
        }

        .card-title {
          font-size: 1.25rem;
          font-weight: 600;
          color: var(--text-primary);
          margin: 0;
          line-height: 1.3;
        }

        .card-badges {
          display: flex;
          gap: 0.5rem;
          flex-wrap: wrap;
        }

        .difficulty-badge,
        .language-badge {
          padding: 0.25rem 0.75rem;
          border-radius: var(--radius-sm);
          font-size: 0.75rem;
          font-weight: 600;
          text-transform: uppercase;
          letter-spacing: 0.025em;
        }

        .card-content {
          flex: 1;
          display: flex;
          flex-direction: column;
          gap: 1rem;
        }

        .card-description {
          color: var(--text-secondary);
          line-height: 1.6;
          margin: 0;
        }

        .complexity-info {
          display: flex;
          flex-direction: column;
          gap: 0.5rem;
        }

        .complexity-item {
          display: flex;
          align-items: center;
          gap: 0.5rem;
          font-size: 0.9rem;
          color: var(--text-secondary);
        }

        .complexity-item svg {
          color: var(--primary-color);
          flex-shrink: 0;
        }

        .tags-section {
          display: flex;
          align-items: center;
          gap: 0.5rem;
        }

        .tags-section svg {
          color: var(--text-muted);
          flex-shrink: 0;
        }

        .tags {
          display: flex;
          flex-wrap: wrap;
          gap: 0.25rem;
        }

        .tag {
          padding: 0.125rem 0.5rem;
          background-color: rgba(99, 102, 241, 0.1);
          color: var(--primary-color);
          border-radius: var(--radius-sm);
          font-size: 0.75rem;
          font-weight: 500;
        }

        .tag.more {
          background-color: var(--bg-tertiary);
          color: var(--text-muted);
        }

        .operations-section {
          margin-top: auto;
        }

        .operations-section h4 {
          font-size: 0.9rem;
          color: var(--text-secondary);
          margin: 0 0 0.5rem 0;
          font-weight: 500;
        }

        .operations {
          display: flex;
          flex-wrap: wrap;
          gap: 0.25rem;
        }

        .operation {
          padding: 0.25rem 0.5rem;
          background-color: rgba(16, 185, 129, 0.1);
          color: var(--secondary-color);
          border-radius: var(--radius-sm);
          font-size: 0.75rem;
          font-weight: 500;
        }

        .operation.more {
          background-color: var(--bg-tertiary);
          color: var(--text-muted);
        }

        .card-actions {
          display: flex;
          gap: 0.75rem;
          margin-top: 1.5rem;
          padding-top: 1rem;
          border-top: 1px solid var(--border-color);
        }

        .card-actions .btn {
          flex: 1;
          justify-content: center;
        }

        .card-footer {
          display: flex;
          justify-content: space-between;
          align-items: center;
          margin-top: 1rem;
          padding-top: 0.75rem;
          border-top: 1px solid var(--border-color);
          font-size: 0.8rem;
          color: var(--text-muted);
        }

        .author-info {
          display: flex;
          align-items: center;
          gap: 0.25rem;
        }

        .update-info {
          font-size: 0.75rem;
        }

        @media (max-width: 480px) {
          .algorithm-card {
            padding: 1rem;
          }

          .card-actions {
            flex-direction: column;
          }

          .card-actions .btn {
            width: 100%;
          }

          .card-footer {
            flex-direction: column;
            align-items: flex-start;
            gap: 0.5rem;
          }
        }
      `}</style>
    </motion.div>
  );
};

export default AlgorithmCard;
