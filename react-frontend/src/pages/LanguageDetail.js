import React from 'react';
import { useParams, Link } from 'react-router-dom';
import { motion } from 'framer-motion';
import { ArrowLeft, Construction } from 'lucide-react';

const LanguageDetail = () => {
  const { id } = useParams();

  return (
    <motion.div
      className="language-detail"
      initial={{ opacity: 0 }}
      animate={{ opacity: 1 }}
      exit={{ opacity: 0 }}
    >
      <div className="container">
        <div className="breadcrumb">
          <Link to="/languages" className="breadcrumb-link">
            <ArrowLeft size={16} />
            Back to Languages
          </Link>
        </div>

        <div className="coming-soon">
          <Construction size={64} />
          <h2>Language Detail Page</h2>
          <p>Individual language pages are under construction.</p>
          <Link to="/languages" className="btn btn-primary">
            Back to Languages
          </Link>
        </div>
      </div>

      <style jsx>{`
        .language-detail {
          padding-top: 70px;
          min-height: 100vh;
          display: flex;
          align-items: center;
        }

        .container {
          max-width: 1200px;
          margin: 0 auto;
          padding: 2rem;
          width: 100%;
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

        .coming-soon {
          display: flex;
          flex-direction: column;
          align-items: center;
          gap: 1.5rem;
          text-align: center;
          color: var(--text-secondary);
        }

        .coming-soon h2 {
          font-size: 2rem;
          color: var(--text-primary);
        }

        .coming-soon p {
          font-size: 1.125rem;
          max-width: 400px;
        }
      `}</style>
    </motion.div>
  );
};

export default LanguageDetail;
