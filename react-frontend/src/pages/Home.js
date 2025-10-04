import React, { useState, useEffect } from 'react';
import { Link } from 'react-router-dom';
import { motion } from 'framer-motion';
import { Helmet } from 'react-helmet-async';
import { 
  ArrowRight, 
  Star, 
  GitFork, 
  Users, 
  Code2,
  Brain,
  Database,
  Rocket,
  Github
} from 'lucide-react';
import { useInView } from 'react-intersection-observer';
import { useGitHub } from '../context/GitHubContext';
import CodeWindow from '../components/CodeWindow';

const Home = () => {
  const [stats, setStats] = useState({
    algorithms: 500,
    dataStructures: 100,
    languages: 6,
    contributors: 1000
  });
  const [repoStats, setRepoStats] = useState({
    stars: 0,
    forks: 0,
    contributors: 0
  });

  const { fetchRepoStats } = useGitHub();
  const [heroRef, heroInView] = useInView({ threshold: 0.3 });
  const [statsRef, statsInView] = useInView({ threshold: 0.5 });

  useEffect(() => {
    const loadRepoStats = async () => {
      const data = await fetchRepoStats();
      setRepoStats(data);
    };
    loadRepoStats();
  }, [fetchRepoStats]);

  const features = [
    {
      icon: Code2,
      title: 'Clean Code',
      description: 'Well-structured, readable implementations with comprehensive documentation'
    },
    {
      icon: Brain,
      title: 'Multiple Languages',
      description: 'Implementations in Java, Python, C++, JavaScript, Go, and C'
    },
    {
      icon: Database,
      title: 'Comprehensive Coverage',
      description: 'From basic sorting to advanced graph algorithms and data structures'
    },
    {
      icon: Rocket,
      title: 'Performance Focused',
      description: 'Optimized algorithms with detailed complexity analysis'
    }
  ];

  const fenwickTreeCode = `public class FenwickTree {
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
}`;

  return (
    <motion.div
      className="home-page"
      initial={{ opacity: 0 }}
      animate={{ opacity: 1 }}
      exit={{ opacity: 0 }}
    >
      <Helmet>
        <title>DSA Code - Master Data Structures & Algorithms</title>
        <meta name="description" content="Comprehensive collection of Data Structures and Algorithms implementations in multiple programming languages. Perfect for learning, practicing, and acing technical interviews." />
      </Helmet>

      {/* Hero Section */}
      <section className="hero-section" ref={heroRef}>
        <div className="hero-background">
          <div className="hero-particles"></div>
        </div>
        
        <div className="container">
          <div className="hero-content">
            <div className="hero-text">
              <motion.h1
                className="hero-title"
                initial={{ opacity: 0, y: 50 }}
                animate={heroInView ? { opacity: 1, y: 0 } : {}}
                transition={{ duration: 0.8 }}
              >
                <span className="title-line">Master</span>
                <span className="title-line highlight">Data Structures</span>
                <span className="title-line">& Algorithms</span>
              </motion.h1>

              <motion.p
                className="hero-description"
                initial={{ opacity: 0, y: 30 }}
                animate={heroInView ? { opacity: 1, y: 0 } : {}}
                transition={{ duration: 0.8, delay: 0.2 }}
              >
                Comprehensive collection of DSA implementations in multiple programming languages. 
                Perfect for learning, practicing, and acing technical interviews.
              </motion.p>

              <motion.div
                className="hero-actions"
                initial={{ opacity: 0, y: 30 }}
                animate={heroInView ? { opacity: 1, y: 0 } : {}}
                transition={{ duration: 0.8, delay: 0.4 }}
              >
                <Link to="/algorithms" className="btn btn-primary btn-lg">
                  <Rocket size={20} />
                  Explore Algorithms
                  <ArrowRight size={20} />
                </Link>
                <a
                  href="https://github.com/Pradeepsingh61/DSA_Code"
                  target="_blank"
                  rel="noopener noreferrer"
                  className="btn btn-outline btn-lg"
                >
                  <Github size={20} />
                  View on GitHub
                </a>
              </motion.div>
            </div>

            <motion.div
              className="hero-visual"
              initial={{ opacity: 0, x: 50 }}
              animate={heroInView ? { opacity: 1, x: 0 } : {}}
              transition={{ duration: 0.8, delay: 0.3 }}
            >
              <CodeWindow
                title="FenwickTree.java"
                language="java"
                code={fenwickTreeCode}
              />
            </motion.div>
          </div>
        </div>
      </section>

      {/* Stats Section */}
      <section className="stats-section" ref={statsRef}>
        <div className="container">
          <div className="stats-grid">
            <motion.div
              className="stat-card"
              initial={{ opacity: 0, y: 30 }}
              animate={statsInView ? { opacity: 1, y: 0 } : {}}
              transition={{ duration: 0.6 }}
            >
              <div className="stat-icon">
                <Brain />
              </div>
              <div className="stat-content">
                <div className="stat-number">{stats.algorithms}+</div>
                <div className="stat-label">Algorithms</div>
              </div>
            </motion.div>

            <motion.div
              className="stat-card"
              initial={{ opacity: 0, y: 30 }}
              animate={statsInView ? { opacity: 1, y: 0 } : {}}
              transition={{ duration: 0.6, delay: 0.1 }}
            >
              <div className="stat-icon">
                <Database />
              </div>
              <div className="stat-content">
                <div className="stat-number">{stats.dataStructures}+</div>
                <div className="stat-label">Data Structures</div>
              </div>
            </motion.div>

            <motion.div
              className="stat-card"
              initial={{ opacity: 0, y: 30 }}
              animate={statsInView ? { opacity: 1, y: 0 } : {}}
              transition={{ duration: 0.6, delay: 0.2 }}
            >
              <div className="stat-icon">
                <Code2 />
              </div>
              <div className="stat-content">
                <div className="stat-number">{stats.languages}</div>
                <div className="stat-label">Languages</div>
              </div>
            </motion.div>

            <motion.div
              className="stat-card"
              initial={{ opacity: 0, y: 30 }}
              animate={statsInView ? { opacity: 1, y: 0 } : {}}
              transition={{ duration: 0.6, delay: 0.3 }}
            >
              <div className="stat-icon">
                <Users />
              </div>
              <div className="stat-content">
                <div className="stat-number">{repoStats.contributors || stats.contributors}+</div>
                <div className="stat-label">Contributors</div>
              </div>
            </motion.div>
          </div>
        </div>
      </section>

      {/* Features Section */}
      <section className="features-section">
        <div className="container">
          <motion.div
            className="section-header"
            initial={{ opacity: 0, y: 30 }}
            whileInView={{ opacity: 1, y: 0 }}
            transition={{ duration: 0.6 }}
            viewport={{ once: true }}
          >
            <h2>Why Choose DSA Code?</h2>
            <p>Everything you need to master data structures and algorithms</p>
          </motion.div>

          <div className="features-grid">
            {features.map((feature, index) => (
              <motion.div
                key={feature.title}
                className="feature-card"
                initial={{ opacity: 0, y: 30 }}
                whileInView={{ opacity: 1, y: 0 }}
                transition={{ duration: 0.6, delay: index * 0.1 }}
                viewport={{ once: true }}
              >
                <div className="feature-icon">
                  <feature.icon size={32} />
                </div>
                <h3>{feature.title}</h3>
                <p>{feature.description}</p>
              </motion.div>
            ))}
          </div>
        </div>
      </section>

      {/* GitHub Stats */}
      <section className="github-stats-section">
        <div className="container">
          <motion.div
            className="github-stats"
            initial={{ opacity: 0, y: 30 }}
            whileInView={{ opacity: 1, y: 0 }}
            transition={{ duration: 0.6 }}
            viewport={{ once: true }}
          >
            <div className="github-stat">
              <Star size={24} />
              <span>{repoStats.stars || '2.5K+'} Stars</span>
            </div>
            <div className="github-stat">
              <GitFork size={24} />
              <span>{repoStats.forks || '500+'} Forks</span>
            </div>
            <div className="github-stat">
              <Users size={24} />
              <span>{repoStats.contributors || '100+'} Contributors</span>
            </div>
          </motion.div>
        </div>
      </section>

      <style jsx>{`
        .home-page {
          padding-top: 70px;
        }

        .hero-section {
          min-height: 100vh;
          display: flex;
          align-items: center;
          position: relative;
          overflow: hidden;
          background: linear-gradient(135deg, var(--bg-primary) 0%, var(--bg-secondary) 100%);
        }

        .hero-background {
          position: absolute;
          top: 0;
          left: 0;
          right: 0;
          bottom: 0;
          opacity: 0.1;
        }

        .hero-particles::before {
          content: '';
          position: absolute;
          top: 0;
          left: 0;
          width: 100%;
          height: 100%;
          background-image: 
            radial-gradient(circle at 20% 50%, rgba(99, 102, 241, 0.1) 0%, transparent 50%),
            radial-gradient(circle at 80% 20%, rgba(16, 185, 129, 0.1) 0%, transparent 50%),
            radial-gradient(circle at 40% 80%, rgba(245, 158, 11, 0.1) 0%, transparent 50%);
          animation: float 20s ease-in-out infinite;
        }

        @keyframes float {
          0%, 100% { transform: translateY(0px) rotate(0deg); }
          33% { transform: translateY(-10px) rotate(1deg); }
          66% { transform: translateY(5px) rotate(-1deg); }
        }

        .hero-content {
          display: grid;
          grid-template-columns: 1fr 1fr;
          gap: 4rem;
          align-items: center;
          position: relative;
          z-index: 1;
        }

        .hero-title {
          font-size: 4rem;
          font-weight: 800;
          line-height: 1.1;
          margin-bottom: 1.5rem;
        }

        .title-line {
          display: block;
        }

        .highlight {
          background: linear-gradient(135deg, var(--primary-color), var(--secondary-color));
          -webkit-background-clip: text;
          -webkit-text-fill-color: transparent;
          background-clip: text;
        }

        .hero-description {
          font-size: 1.25rem;
          color: var(--text-secondary);
          margin-bottom: 2rem;
          line-height: 1.7;
        }

        .hero-actions {
          display: flex;
          gap: 1rem;
          flex-wrap: wrap;
        }

        .stats-section {
          padding: 6rem 0;
          background-color: var(--bg-secondary);
        }

        .stats-grid {
          display: grid;
          grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
          gap: 2rem;
        }

        .stat-card {
          background-color: var(--bg-card);
          border: 1px solid var(--border-color);
          border-radius: var(--radius-xl);
          padding: 2rem;
          text-align: center;
          transition: all var(--transition-normal);
        }

        .stat-card:hover {
          transform: translateY(-5px);
          box-shadow: var(--shadow-lg);
        }

        .stat-icon {
          color: var(--primary-color);
          margin-bottom: 1rem;
          display: flex;
          justify-content: center;
        }

        .stat-number {
          font-size: 3rem;
          font-weight: 700;
          color: var(--primary-color);
          margin-bottom: 0.5rem;
        }

        .stat-label {
          color: var(--text-secondary);
          font-size: 1.1rem;
        }

        .features-section {
          padding: 6rem 0;
        }

        .section-header {
          text-align: center;
          margin-bottom: 4rem;
        }

        .section-header h2 {
          font-size: 3rem;
          font-weight: 700;
          margin-bottom: 1rem;
        }

        .section-header p {
          font-size: 1.25rem;
          color: var(--text-secondary);
        }

        .features-grid {
          display: grid;
          grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
          gap: 2rem;
        }

        .feature-card {
          background-color: var(--bg-card);
          border: 1px solid var(--border-color);
          border-radius: var(--radius-xl);
          padding: 2rem;
          text-align: center;
          transition: all var(--transition-normal);
        }

        .feature-card:hover {
          transform: translateY(-5px);
          box-shadow: var(--shadow-lg);
          border-color: var(--primary-color);
        }

        .feature-icon {
          color: var(--primary-color);
          margin-bottom: 1.5rem;
          display: flex;
          justify-content: center;
        }

        .feature-card h3 {
          font-size: 1.5rem;
          font-weight: 600;
          margin-bottom: 1rem;
        }

        .feature-card p {
          color: var(--text-secondary);
          line-height: 1.6;
        }

        .github-stats-section {
          padding: 4rem 0;
          background-color: var(--bg-secondary);
        }

        .github-stats {
          display: flex;
          justify-content: center;
          gap: 3rem;
          flex-wrap: wrap;
        }

        .github-stat {
          display: flex;
          align-items: center;
          gap: 0.5rem;
          color: var(--text-primary);
          font-weight: 600;
          font-size: 1.1rem;
        }

        @media (max-width: 768px) {
          .hero-content {
            grid-template-columns: 1fr;
            gap: 3rem;
            text-align: center;
          }

          .hero-title {
            font-size: 2.5rem;
          }

          .hero-actions {
            justify-content: center;
          }

          .stats-grid {
            grid-template-columns: repeat(2, 1fr);
            gap: 1rem;
          }

          .features-grid {
            grid-template-columns: 1fr;
          }

          .github-stats {
            gap: 2rem;
          }
        }

        @media (max-width: 480px) {
          .stats-grid {
            grid-template-columns: 1fr;
          }

          .github-stats {
            flex-direction: column;
            align-items: center;
            gap: 1rem;
          }
        }
      `}</style>
    </motion.div>
  );
};

export default Home;
