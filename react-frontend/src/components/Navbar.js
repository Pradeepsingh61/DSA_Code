import React, { useState, useEffect } from 'react';
import { Link, useLocation } from 'react-router-dom';
import { motion } from 'framer-motion';
import { 
  Code, 
  Menu, 
  X, 
  Sun, 
  Moon, 
  Github,
  Brain,
  Database,
  Languages,
  Users,
  Info
} from 'lucide-react';
import { useTheme } from '../context/ThemeContext';

const Navbar = () => {
  const [isOpen, setIsOpen] = useState(false);
  const [scrolled, setScrolled] = useState(false);
  const { theme, toggleTheme } = useTheme();
  const location = useLocation();

  useEffect(() => {
    const handleScroll = () => {
      setScrolled(window.scrollY > 50);
    };

    window.addEventListener('scroll', handleScroll);
    return () => window.removeEventListener('scroll', handleScroll);
  }, []);

  const navItems = [
    { path: '/', label: 'Home', icon: Code },
    { path: '/algorithms', label: 'Algorithms', icon: Brain },
    { path: '/data-structures', label: 'Data Structures', icon: Database },
    { path: '/languages', label: 'Languages', icon: Languages },
    { path: '/contribute', label: 'Contribute', icon: Users },
    { path: '/about', label: 'About', icon: Info }
  ];

  const isActive = (path) => {
    if (path === '/') {
      return location.pathname === '/';
    }
    return location.pathname.startsWith(path);
  };

  return (
    <motion.nav
      className={`navbar ${scrolled ? 'scrolled' : ''}`}
      initial={{ y: -100 }}
      animate={{ y: 0 }}
      transition={{ duration: 0.5 }}
    >
      <div className="nav-container">
        <div className="nav-content">
          {/* Brand */}
          <Link to="/" className="nav-brand">
            <Code size={32} />
            <span>DSA Code</span>
          </Link>

          {/* Desktop Navigation */}
          <div className="nav-menu desktop-only">
            {navItems.map(({ path, label, icon: Icon }) => (
              <Link
                key={path}
                to={path}
                className={`nav-link ${isActive(path) ? 'active' : ''}`}
              >
                <Icon size={18} />
                <span>{label}</span>
              </Link>
            ))}
          </div>

          {/* Actions */}
          <div className="nav-actions">
            <button
              onClick={toggleTheme}
              className="theme-toggle"
              aria-label="Toggle theme"
            >
              {theme === 'dark' ? <Sun size={20} /> : <Moon size={20} />}
            </button>

            <a
              href="https://github.com/Pradeepsingh61/DSA_Code"
              target="_blank"
              rel="noopener noreferrer"
              className="github-btn"
            >
              <Github size={18} />
              <span className="desktop-only">GitHub</span>
            </a>

            <button
              className="mobile-menu-toggle mobile-only"
              onClick={() => setIsOpen(!isOpen)}
              aria-label="Toggle menu"
            >
              {isOpen ? <X size={24} /> : <Menu size={24} />}
            </button>
          </div>
        </div>

        {/* Mobile Navigation */}
        <motion.div
          className={`mobile-menu ${isOpen ? 'open' : ''}`}
          initial={false}
          animate={{ height: isOpen ? 'auto' : 0 }}
          transition={{ duration: 0.3 }}
        >
          <div className="mobile-menu-content">
            {navItems.map(({ path, label, icon: Icon }) => (
              <Link
                key={path}
                to={path}
                className={`mobile-nav-link ${isActive(path) ? 'active' : ''}`}
                onClick={() => setIsOpen(false)}
              >
                <Icon size={18} />
                <span>{label}</span>
              </Link>
            ))}
          </div>
        </motion.div>
      </div>

      <style jsx>{`
        .navbar {
          position: fixed;
          top: 0;
          left: 0;
          right: 0;
          background: rgba(255, 255, 255, 0.95);
          backdrop-filter: blur(10px);
          border-bottom: 1px solid #e2e8f0;
          z-index: 1020;
          transition: all 0.3s ease;
        }

        .nav-container {
          max-width: 1200px;
          margin: 0 auto;
          padding: 0 2rem;
        }

        [data-theme="dark"] .navbar {
          background: rgba(15, 23, 42, 0.95);
        }

        .navbar.scrolled {
          background: rgba(255, 255, 255, 0.98);
          box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.1);
        }

        [data-theme="dark"] .navbar.scrolled {
          background: rgba(15, 23, 42, 0.98);
        }

        .nav-content {
          display: flex;
          align-items: center;
          justify-content: space-between;
          height: 70px;
        }

        .nav-brand {
          display: flex;
          align-items: center;
          gap: 0.5rem;
          font-size: 1.5rem;
          font-weight: 700;
          color: #6366f1;
          text-decoration: none;
        }

        .nav-menu {
          display: flex !important;
          flex-direction: row !important;
          align-items: center !important;
          gap: 1.5rem !important;
          margin: 0 !important;
          padding: 0 !important;
        }

        .nav-link {
          display: flex !important;
          flex-direction: row !important;
          align-items: center !important;
          gap: 0.5rem !important;
          padding: 0.5rem 1rem !important;
          color: #64748b !important;
          text-decoration: none !important;
          border-radius: 0.5rem !important;
          transition: all 0.15s ease !important;
          font-weight: 500 !important;
          white-space: nowrap !important;
          min-width: auto !important;
        }

        .nav-link:hover,
        .nav-link.active {
          color: #6366f1 !important;
          background-color: rgba(99, 102, 241, 0.1) !important;
        }

        .nav-actions {
          display: flex;
          align-items: center;
          gap: 1rem;
        }

        .theme-toggle {
          background: none;
          border: none;
          color: #64748b;
          cursor: pointer;
          padding: 0.5rem;
          border-radius: 0.5rem;
          transition: all 0.15s ease;
        }

        .theme-toggle:hover {
          color: #6366f1;
          background-color: rgba(99, 102, 241, 0.1);
        }

        .github-btn {
          display: flex;
          align-items: center;
          gap: 0.5rem;
          padding: 0.5rem 1rem;
          background-color: #1e293b;
          color: #ffffff;
          text-decoration: none;
          border-radius: 0.5rem;
          font-weight: 500;
          transition: all 0.15s ease;
        }

        .github-btn:hover {
          background-color: #6366f1;
          transform: translateY(-2px);
        }

        .mobile-menu-toggle {
          background: none;
          border: none;
          color: #1e293b;
          cursor: pointer;
          padding: 0.5rem;
        }

        .mobile-menu {
          overflow: hidden;
          background-color: #ffffff;
          border-top: 1px solid #e2e8f0;
        }

        [data-theme="dark"] .mobile-menu {
          background-color: #0f172a;
        }

        .mobile-menu-content {
          padding: 1rem 0;
        }

        .mobile-nav-link {
          display: flex;
          align-items: center;
          gap: 1rem;
          padding: 1rem;
          color: var(--text-secondary);
          text-decoration: none;
          transition: all var(--transition-fast);
          font-weight: 500;
        }

        .mobile-nav-link:hover,
        .mobile-nav-link.active {
          color: var(--primary-color);
          background-color: rgba(99, 102, 241, 0.1);
        }

        .desktop-only {
          display: flex !important;
        }

        .mobile-only {
          display: none !important;
        }

        @media (max-width: 768px) {
          .desktop-only {
            display: none !important;
          }

          .mobile-only {
            display: block !important;
          }

          .nav-menu {
            display: none !important;
          }
        }
      `}</style>
    </motion.nav>
  );
};

export default Navbar;
