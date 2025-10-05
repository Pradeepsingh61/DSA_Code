import React from 'react';
import { motion } from 'framer-motion';
import { Helmet } from 'react-helmet-async';
import { Languages as LanguagesIcon, Construction } from 'lucide-react';
import { Link } from 'react-router-dom';

const Languages = () => {
  return (
    <motion.div
      className="languages-page"
      initial={{ opacity: 0 }}
      animate={{ opacity: 1 }}
      exit={{ opacity: 0 }}
    >
      <Helmet>
        <title>Programming Languages - DSA Code</title>
        <meta name="description" content="Explore DSA implementations across multiple programming languages" />
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
              <LanguagesIcon size={48} />
            </div>
            <h1>Programming Languages</h1>
            <p>Implementations available in multiple programming languages</p>
          </motion.div>
        </div>
      </div>

      <div className="page-content">
        <div className="container">
          <motion.div
            className="coming-soon"
            initial={{ opacity: 0, y: 30 }}
            animate={{ opacity: 1, y: 0 }}
            transition={{ duration: 0.6, delay: 0.2 }}
          >
            <Construction size={64} />
            <h2>Coming Soon</h2>
            <p>Languages page is under construction. Check back soon!</p>
            <Link to="/algorithms" className="btn btn-primary">
              Explore Algorithms Instead
            </Link>
          </motion.div>
        </div>
      </div>

      <style jsx>{`
        .languages-page {
          padding-top: 70px;
          min-height: 100vh;
        }

        .page-header {
          background: linear-gradient(135deg, var(--accent-color), var(--primary-color));
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

        .header-content h1 {
          font-size: 3rem;
          font-weight: 700;
          margin: 0;
        }

        .header-content p {
          font-size: 1.25rem;
          opacity: 0.9;
          margin: 0;
        }

        .page-content {
          padding: 6rem 0;
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

export default Languages;
