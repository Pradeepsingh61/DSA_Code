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
      <div className="container">
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
          border-bottom: 1px solid var(--border-color);
          z-index: var(--z-sticky);
          transition: all var(--transition-normal);
        }

        [data-theme="dark"] .navbar {
          background: rgba(15, 23, 42, 0.95);
        }

        .navbar.scrolled {
          background: rgba(255, 255, 255, 0.98);
          box-shadow: var(--shadow-md);
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
          color: var(--primary-color);
          text-decoration: none;
        }

        .nav-menu {
          display: flex;
          align-items: center;
          gap: 2rem;
        }

        .nav-link {
          display: flex;
          align-items: center;
          gap: 0.5rem;
          padding: 0.5rem 1rem;
          color: var(--text-secondary);
          text-decoration: none;
          border-radius: var(--radius-md);
          transition: all var(--transition-fast);
          font-weight: 500;
        }

        .nav-link:hover,
        .nav-link.active {
          color: var(--primary-color);
          background-color: rgba(99, 102, 241, 0.1);
        }

        .nav-actions {
          display: flex;
          align-items: center;
          gap: 1rem;
        }

        .theme-toggle {
          background: none;
          border: none;
          color: var(--text-secondary);
          cursor: pointer;
          padding: 0.5rem;
          border-radius: var(--radius-md);
          transition: all var(--transition-fast);
        }

        .theme-toggle:hover {
          color: var(--primary-color);
          background-color: rgba(99, 102, 241, 0.1);
        }

        .github-btn {
          display: flex;
          align-items: center;
          gap: 0.5rem;
          padding: 0.5rem 1rem;
          background-color: var(--text-primary);
          color: var(--text-inverse);
          text-decoration: none;
          border-radius: var(--radius-md);
          font-weight: 500;
          transition: all var(--transition-fast);
        }

        .github-btn:hover {
          background-color: var(--primary-color);
          transform: translateY(-2px);
        }

        .mobile-menu-toggle {
          background: none;
          border: none;
          color: var(--text-primary);
          cursor: pointer;
          padding: 0.5rem;
        }

        .mobile-menu {
          overflow: hidden;
          background-color: var(--bg-primary);
          border-top: 1px solid var(--border-color);
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
          display: block;
        }

        .mobile-only {
          display: none;
        }

        @media (max-width: 768px) {
          .desktop-only {
            display: none;
          }

          .mobile-only {
            display: block;
          }

          .nav-menu {
            display: none;
          }
        }
      `}</style>
    </motion.nav>
  );
};

export default Navbar;
