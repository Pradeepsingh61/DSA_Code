import React, { useState, useEffect } from 'react';
import { Routes, Route } from 'react-router-dom';
import { motion, AnimatePresence } from 'framer-motion';
import { Helmet } from 'react-helmet-async';

// Components
import Navbar from './components/Navbar';
import Footer from './components/Footer';
import LoadingScreen from './components/LoadingScreen';
import ScrollToTop from './components/ScrollToTop';

// Pages
import Home from './pages/Home';
import Algorithms from './pages/Algorithms';
import AlgorithmDetail from './pages/AlgorithmDetail';
import DataStructures from './pages/DataStructures';
import DataStructureDetail from './pages/DataStructureDetail';
import Languages from './pages/Languages';
import LanguageDetail from './pages/LanguageDetail';
import Contribute from './pages/Contribute';
import About from './pages/About';
import NotFound from './pages/NotFound';

// Context
import { ThemeProvider } from './context/ThemeContext';
import { GitHubProvider } from './context/GitHubContext';

function App() {
  const [isLoading, setIsLoading] = useState(true);

  useEffect(() => {
    // Simulate loading time
    const timer = setTimeout(() => {
      setIsLoading(false);
    }, 2000);

    return () => clearTimeout(timer);
  }, []);

  if (isLoading) {
    return <LoadingScreen />;
  }

  return (
    <ThemeProvider>
      <GitHubProvider>
        <div className="App">
          <Helmet>
            <title>DSA Code - Data Structures & Algorithms Hub</title>
            <meta name="description" content="Comprehensive collection of Data Structures and Algorithms implementations in multiple programming languages" />
          </Helmet>
          
          <Navbar />
          
          <main className="main-content">
            <AnimatePresence mode="wait">
              <Routes>
                <Route path="/" element={<Home />} />
                <Route path="/algorithms" element={<Algorithms />} />
                <Route path="/algorithms/:id" element={<AlgorithmDetail />} />
                <Route path="/data-structures" element={<DataStructures />} />
                <Route path="/data-structures/:id" element={<DataStructureDetail />} />
                <Route path="/languages" element={<Languages />} />
                <Route path="/languages/:id" element={<LanguageDetail />} />
                <Route path="/contribute" element={<Contribute />} />
                <Route path="/about" element={<About />} />
                <Route path="*" element={<NotFound />} />
              </Routes>
            </AnimatePresence>
          </main>
          
          <Footer />
          <ScrollToTop />
        </div>
      </GitHubProvider>
    </ThemeProvider>
  );
}

export default App;
