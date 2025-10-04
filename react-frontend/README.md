# DSA Code React Frontend

A modern, responsive React application for the DSA_Code repository showcasing data structures and algorithms implementations with real GitHub integration.

## 🌟 Features

### ✨ Modern React Architecture
- **React 18** with hooks and functional components
- **React Router v6** for client-side routing
- **Framer Motion** for smooth animations
- **Context API** for state management
- **React Helmet Async** for SEO optimization

### 🔍 Real GitHub Integration
- **GitHub API** integration for fetching real repository data
- **Live code viewing** directly from GitHub
- **Real-time statistics** (stars, forks, contributors)
- **Dynamic content** loading from repository files

### 🎨 Modern UI/UX
- **Responsive Design** - Works on all devices
- **Dark/Light Theme** with system preference detection
- **Smooth Animations** using Framer Motion
- **Syntax Highlighting** with Prism.js
- **Interactive Components** with hover effects

### 📱 Key Pages
- **Home** - Hero section with animated statistics
- **Algorithms** - Comprehensive algorithm browser with search/filter
- **Algorithm Detail** - Individual algorithm pages with real code
- **Data Structures** - Data structure implementations
- **Languages** - Multi-language support showcase
- **Contribute** - Community contribution guide

## 🚀 Quick Start

### Prerequisites
- Node.js 16+ and npm/yarn
- Modern web browser

### Installation

1. **Clone and navigate**
   ```bash
   git clone https://github.com/Pradeepsingh61/DSA_Code.git
   cd DSA_Code/react-frontend
   ```

2. **Install dependencies**
   ```bash
   npm install
   # or
   yarn install
   ```

3. **Start development server**
   ```bash
   npm start
   # or
   yarn start
   ```

4. **Open browser**
   Visit `http://localhost:3000`

## 📁 Project Structure

```
react-frontend/
├── public/
│   ├── index.html          # HTML template
│   └── manifest.json       # PWA manifest
├── src/
│   ├── components/         # Reusable components
│   │   ├── Navbar.js      # Navigation component
│   │   ├── Footer.js      # Footer component
│   │   ├── CodeWindow.js  # Code display component
│   │   ├── AlgorithmCard.js # Algorithm card component
│   │   ├── LoadingScreen.js # Loading animation
│   │   └── ScrollToTop.js # Scroll to top button
│   ├── pages/             # Page components
│   │   ├── Home.js        # Landing page
│   │   ├── Algorithms.js  # Algorithms listing
│   │   ├── AlgorithmDetail.js # Individual algorithm page
│   │   ├── DataStructures.js # Data structures page
│   │   ├── Languages.js   # Languages page
│   │   ├── Contribute.js  # Contribution guide
│   │   ├── About.js       # About page
│   │   └── NotFound.js    # 404 page
│   ├── context/           # React Context providers
│   │   ├── ThemeContext.js # Theme management
│   │   └── GitHubContext.js # GitHub API integration
│   ├── App.js            # Main app component
│   ├── index.js          # App entry point
│   └── index.css         # Global styles
├── package.json          # Dependencies and scripts
└── README.md            # This file
```

## 🎨 Design System

### Color Palette
- **Primary**: `#6366f1` (Indigo)
- **Secondary**: `#10b981` (Emerald)
- **Accent**: `#f59e0b` (Amber)
- **Danger**: `#ef4444` (Red)

### Typography
- **UI Font**: Inter (Google Fonts)
- **Code Font**: JetBrains Mono (Google Fonts)

### Components
- **Cards** with hover animations
- **Buttons** with multiple variants
- **Code Windows** with syntax highlighting
- **Responsive Navigation** with mobile menu
- **Loading States** with spinners

## 🔧 Key Features Implementation

### GitHub Integration
```javascript
// Real-time repository data fetching
const { fetchRepoStats, fetchFileContent } = useGitHub();

// Get live repository statistics
const stats = await fetchRepoStats();

// Fetch actual code from GitHub
const code = await fetchFileContent('Java/algorithms/sorting/QuickSort.java');
```

### Theme Management
```javascript
// Context-based theme switching
const { theme, toggleTheme } = useTheme();

// Persistent theme storage
localStorage.setItem('dsa-code-theme', theme);
```

### Routing with Animation
```javascript
// Animated page transitions
<AnimatePresence mode="wait">
  <Routes>
    <Route path="/" element={<Home />} />
    <Route path="/algorithms" element={<Algorithms />} />
    <Route path="/algorithms/:id" element={<AlgorithmDetail />} />
  </Routes>
</AnimatePresence>
```

## 📊 Performance Optimizations

- **Code Splitting** with React.lazy()
- **Image Optimization** with lazy loading
- **Bundle Optimization** with Create React App
- **Caching Strategy** for GitHub API calls
- **Responsive Images** for different screen sizes

## 🌐 Deployment

### GitHub Pages
```bash
npm run build
npm run deploy
```

### Netlify
1. Connect repository to Netlify
2. Set build command: `npm run build`
3. Set publish directory: `build`
4. Deploy automatically on push

### Vercel
1. Import project to Vercel
2. Zero-configuration deployment
3. Automatic deployments on push

## 🔍 SEO Optimization

- **React Helmet Async** for meta tags
- **Open Graph** tags for social sharing
- **Twitter Cards** for Twitter sharing
- **Structured Data** for search engines
- **Sitemap Generation** for better indexing

## 📱 Progressive Web App

- **Service Worker** for offline functionality
- **Web App Manifest** for installability
- **Responsive Design** for all devices
- **Fast Loading** with optimized assets

## 🧪 Testing

```bash
# Run tests
npm test

# Run tests with coverage
npm test -- --coverage

# Run tests in watch mode
npm test -- --watch
```

## 🚀 Build and Deploy

```bash
# Create production build
npm run build

# Deploy to GitHub Pages
npm run deploy

# Analyze bundle size
npm run analyze
```

## 🤝 Contributing

1. **Fork the repository**
2. **Create feature branch**: `git checkout -b feature/amazing-feature`
3. **Install dependencies**: `npm install`
4. **Start development**: `npm start`
5. **Make changes** and test thoroughly
6. **Commit changes**: `git commit -m 'Add amazing feature'`
7. **Push to branch**: `git push origin feature/amazing-feature`
8. **Open Pull Request**

### Development Guidelines
- Follow React best practices
- Use functional components with hooks
- Implement responsive design
- Add proper error handling
- Write meaningful commit messages
- Test on multiple browsers

## 📝 Environment Variables

Create `.env` file for configuration:
```env
REACT_APP_GITHUB_TOKEN=your_github_token_here
REACT_APP_REPO_OWNER=Pradeepsingh61
REACT_APP_REPO_NAME=DSA_Code
```

## 🐛 Troubleshooting

### Common Issues
- **Build fails**: Clear node_modules and reinstall
- **GitHub API rate limit**: Add GitHub token to .env
- **Routing issues**: Ensure basename is set correctly
- **Theme not persisting**: Check localStorage permissions

## 📞 Support

- **Issues**: [GitHub Issues](https://github.com/Pradeepsingh61/DSA_Code/issues)
- **Discussions**: [GitHub Discussions](https://github.com/Pradeepsingh61/DSA_Code/discussions)
- **Documentation**: [Main README](../README.md)

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](../LICENSE) file for details.

---

**Built with ❤️ using React and modern web technologies**
