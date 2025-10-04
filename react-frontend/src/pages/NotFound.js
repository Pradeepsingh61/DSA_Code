import React from 'react';
import { Link } from 'react-router-dom';
import { motion } from 'framer-motion';
import { Home, Search, ArrowLeft } from 'lucide-react';

const NotFound = () => {
  return (
    <motion.div
      className="not-found-page"
      initial={{ opacity: 0 }}
      animate={{ opacity: 1 }}
      exit={{ opacity: 0 }}
    >
      <div className="container">
        <motion.div
          className="not-found-content"
          initial={{ opacity: 0, y: 30 }}
          animate={{ opacity: 1, y: 0 }}
          transition={{ duration: 0.6 }}
        >
          <div className="error-code">404</div>
          <h1>Page Not Found</h1>
          <p>
            The page you're looking for doesn't exist or has been moved.
            Let's get you back on track!
          </p>
          
          <div className="action-buttons">
            <Link to="/" className="btn btn-primary">
              <Home size={16} />
              Go Home
            </Link>
            <Link to="/algorithms" className="btn btn-secondary">
              <Search size={16} />
              Browse Algorithms
            </Link>
          </div>
        </motion.div>
      </div>

      <style jsx>{`
        .not-found-page {
          padding-top: 70px;
          min-height: 100vh;
          display: flex;
          align-items: center;
          justify-content: center;
          background: linear-gradient(135deg, var(--bg-primary) 0%, var(--bg-secondary) 100%);
        }

        .not-found-content {
          text-align: center;
          max-width: 500px;
        }

        .error-code {
          font-size: 8rem;
          font-weight: 800;
          background: linear-gradient(135deg, var(--primary-color), var(--secondary-color));
          -webkit-background-clip: text;
          -webkit-text-fill-color: transparent;
          background-clip: text;
          line-height: 1;
          margin-bottom: 1rem;
        }

        .not-found-content h1 {
          font-size: 2.5rem;
          font-weight: 700;
          margin-bottom: 1rem;
          color: var(--text-primary);
        }

        .not-found-content p {
          font-size: 1.125rem;
          color: var(--text-secondary);
          line-height: 1.6;
          margin-bottom: 2rem;
        }

        .action-buttons {
          display: flex;
          gap: 1rem;
          justify-content: center;
          flex-wrap: wrap;
        }

        @media (max-width: 768px) {
          .error-code {
            font-size: 6rem;
          }

          .not-found-content h1 {
            font-size: 2rem;
          }

          .not-found-content p {
            font-size: 1rem;
          }

          .action-buttons {
            flex-direction: column;
            align-items: center;
          }

          .action-buttons .btn {
            width: 200px;
          }
        }
      `}</style>
    </motion.div>
  );
};

export default NotFound;
