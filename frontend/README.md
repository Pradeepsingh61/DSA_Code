# DSA Code Frontend

A modern, responsive web interface for the DSA_Code repository showcasing data structures and algorithms implementations.

## 🌟 Features

### ✨ Modern UI/UX
- **Responsive Design** - Works perfectly on desktop, tablet, and mobile
- **Dark/Light Theme** - Toggle between themes with smooth transitions
- **Smooth Animations** - Engaging micro-interactions and page transitions
- **Modern Typography** - Clean, readable fonts (Inter + JetBrains Mono)
- **Glassmorphism Effects** - Modern blur and transparency effects

### 🔍 Interactive Features
- **Live Search** - Real-time algorithm and data structure search
- **Category Filtering** - Filter by algorithm categories (sorting, searching, graph, etc.)
- **Code Preview** - View algorithm implementations directly in the browser
- **GitHub Integration** - Direct links to source code on GitHub
- **Performance Metrics** - Time and space complexity information

### 📱 Responsive Components
- **Navigation Bar** - Sticky navigation with smooth scrolling
- **Hero Section** - Animated statistics and call-to-action buttons
- **Algorithm Cards** - Interactive cards with hover effects
- **Data Structure Showcase** - Detailed operation listings
- **Language Support** - Multi-language implementation showcase
- **Contribution Guide** - Step-by-step contribution instructions

## 🚀 Quick Start

### Prerequisites
- Modern web browser (Chrome, Firefox, Safari, Edge)
- Local web server (optional, for development)

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/Pradeepsingh61/DSA_Code.git
   cd DSA_Code/frontend
   ```

2. **Open in browser**
   ```bash
   # Option 1: Direct file opening
   open index.html
   
   # Option 2: Local server (recommended)
   python -m http.server 8000
   # Then visit http://localhost:8000
   
   # Option 3: Using Node.js
   npx serve .
   ```

3. **Start exploring!**
   - Browse algorithms by category
   - Search for specific implementations
   - Toggle between light and dark themes
   - View code directly in the browser

## 📁 Project Structure

```
frontend/
├── index.html              # Main HTML file
├── css/
│   ├── style.css          # Main styles and variables
│   ├── components.css     # Component-specific styles
│   └── animations.css     # Animation definitions
├── js/
│   ├── main.js           # Main application logic
│   ├── data.js           # Algorithm and data structure data
│   ├── components.js     # Reusable components
│   └── animations.js     # Animation controllers
├── assets/
│   ├── images/           # Images and icons
│   └── favicon.ico       # Site favicon
└── README.md            # This file
```

## 🎨 Design System

### Color Palette
- **Primary**: `#6366f1` (Indigo)
- **Secondary**: `#10b981` (Emerald)
- **Accent**: `#f59e0b` (Amber)
- **Danger**: `#ef4444` (Red)

### Typography
- **Headings**: Inter (300-800 weights)
- **Body**: Inter (400-600 weights)
- **Code**: JetBrains Mono (400-600 weights)

### Spacing System
- **XS**: 0.25rem (4px)
- **SM**: 0.5rem (8px)
- **MD**: 1rem (16px)
- **LG**: 1.5rem (24px)
- **XL**: 2rem (32px)
- **2XL**: 3rem (48px)

## 🔧 Customization

### Adding New Algorithms
1. Update `js/data.js` with algorithm information:
   ```javascript
   {
     name: 'Your Algorithm',
     category: 'sorting',
     language: 'Java',
     difficulty: 'Medium',
     description: 'Algorithm description',
     timeComplexity: 'O(n log n)',
     spaceComplexity: 'O(n)',
     path: 'path/to/algorithm.java'
   }
   ```

### Modifying Themes
1. Edit CSS variables in `css/style.css`:
   ```css
   :root {
     --primary-color: #your-color;
     --bg-primary: #your-bg-color;
   }
   ```

### Adding New Sections
1. Add HTML section in `index.html`
2. Add corresponding navigation link
3. Update JavaScript navigation logic in `main.js`

## 🌐 Browser Support

- **Chrome**: 90+
- **Firefox**: 88+
- **Safari**: 14+
- **Edge**: 90+

## 📊 Performance Features

- **Lazy Loading** - Images and content loaded on demand
- **CSS Grid & Flexbox** - Modern layout techniques
- **Hardware Acceleration** - GPU-accelerated animations
- **Optimized Assets** - Compressed images and minified code
- **Caching Strategy** - Browser caching for static assets

## 🎯 Key Components

### Navigation System
- Smooth scrolling between sections
- Active state management
- Mobile-responsive hamburger menu
- Theme toggle functionality

### Search & Filter
- Real-time search across algorithms
- Category-based filtering
- Responsive filter tabs
- Search result highlighting

### Algorithm Cards
- Hover animations and effects
- Complexity information display
- Direct GitHub integration
- Modal code preview

### Data Structure Showcase
- Operation listings
- Time complexity matrices
- Interactive demonstrations
- Implementation examples

## 🚀 Deployment

### GitHub Pages
1. Push to `gh-pages` branch
2. Enable GitHub Pages in repository settings
3. Access via `https://username.github.io/DSA_Code/frontend/`

### Netlify
1. Connect repository to Netlify
2. Set build directory to `frontend/`
3. Deploy automatically on push

### Vercel
1. Import project to Vercel
2. Set root directory to `frontend/`
3. Deploy with zero configuration

## 🤝 Contributing

1. **Fork the repository**
2. **Create feature branch**: `git checkout -b feature/amazing-feature`
3. **Make changes** to frontend files
4. **Test thoroughly** across different browsers
5. **Commit changes**: `git commit -m 'Add amazing feature'`
6. **Push to branch**: `git push origin feature/amazing-feature`
7. **Open Pull Request**

### Frontend Contribution Guidelines
- Follow existing code style and structure
- Test on multiple browsers and devices
- Ensure accessibility compliance
- Optimize for performance
- Update documentation as needed

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](../LICENSE) file for details.

## 🙏 Acknowledgments

- **Inter Font** by Rasmus Andersson
- **JetBrains Mono** by JetBrains
- **Font Awesome** for icons
- **CSS Grid** and **Flexbox** for layouts
- **Intersection Observer API** for animations

## 📞 Support

- **Issues**: [GitHub Issues](https://github.com/Pradeepsingh61/DSA_Code/issues)
- **Discussions**: [GitHub Discussions](https://github.com/Pradeepsingh61/DSA_Code/discussions)
- **Documentation**: [Main README](../README.md)

---

**Made with ❤️ by the DSA Code community**
