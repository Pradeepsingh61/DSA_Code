# Deployment Guide

Complete guide for deploying the DSA Code React frontend to various platforms.

## 🚀 Quick Deploy Options

### 1. GitHub Pages (Recommended)
**Free hosting with custom domain support**

#### Automatic Deployment
```bash
# The app auto-deploys when you push to main branch
git push origin main
```

#### Manual Deployment
```bash
npm run build
npm run deploy
```

#### Setup GitHub Pages
1. Go to repository Settings → Pages
2. Select "Deploy from a branch"
3. Choose `gh-pages` branch
4. Custom domain: `dsa-code.dev` (optional)

### 2. Netlify
**Easy deployment with continuous integration**

#### Method 1: Git Integration
1. Connect your GitHub repository to Netlify
2. Set build settings:
   - **Build command**: `npm run build`
   - **Publish directory**: `build`
   - **Base directory**: `react-frontend`
3. Deploy automatically on every push

#### Method 2: Manual Deploy
```bash
npm run build
# Drag and drop the 'build' folder to Netlify
```

#### Environment Variables on Netlify
```bash
# In Netlify dashboard → Site settings → Environment variables
REACT_APP_GITHUB_TOKEN=your_token_here
REACT_APP_REPO_OWNER=Pradeepsingh61
REACT_APP_REPO_NAME=DSA_Code
```

### 3. Vercel
**Zero-configuration deployment**

#### Method 1: Vercel CLI
```bash
npm install -g vercel
cd react-frontend
vercel
```

#### Method 2: Git Integration
1. Import project to Vercel
2. Set root directory to `react-frontend`
3. Deploy automatically

#### Environment Variables on Vercel
```bash
# In Vercel dashboard → Settings → Environment Variables
REACT_APP_GITHUB_TOKEN=your_token_here
REACT_APP_REPO_OWNER=Pradeepsingh61
REACT_APP_REPO_NAME=DSA_Code
```

### 4. Firebase Hosting
**Google's hosting platform**

#### Setup
```bash
npm install -g firebase-tools
firebase login
firebase init hosting
```

#### Deploy
```bash
npm run build
firebase deploy
```

#### Configuration (firebase.json)
```json
{
  "hosting": {
    "public": "build",
    "ignore": ["firebase.json", "**/.*", "**/node_modules/**"],
    "rewrites": [
      {
        "source": "**",
        "destination": "/index.html"
      }
    ]
  }
}
```

### 5. AWS S3 + CloudFront
**Scalable cloud hosting**

#### Build and Upload
```bash
npm run build
aws s3 sync build/ s3://your-bucket-name --delete
aws cloudfront create-invalidation --distribution-id YOUR_DISTRIBUTION_ID --paths "/*"
```

#### S3 Bucket Configuration
- Enable static website hosting
- Set index document: `index.html`
- Set error document: `index.html`

## 🔧 Build Configuration

### Production Build
```bash
# Create optimized production build
npm run build

# Analyze bundle size
npm run analyze
```

### Build Output
```
build/
├── static/
│   ├── css/           # Minified CSS files
│   ├── js/            # Minified JavaScript bundles
│   └── media/         # Optimized images and fonts
├── index.html         # Main HTML file
└── manifest.json      # PWA manifest
```

### Build Optimization
- **Code Splitting**: Automatic with React.lazy()
- **Tree Shaking**: Removes unused code
- **Minification**: CSS and JS compression
- **Asset Optimization**: Image and font optimization

## 🌐 Custom Domain Setup

### GitHub Pages
1. Add `CNAME` file to `public/` folder:
   ```
   dsa-code.dev
   ```
2. Configure DNS:
   ```
   Type: CNAME
   Name: www
   Value: username.github.io
   ```

### Netlify
1. Go to Domain settings
2. Add custom domain: `dsa-code.dev`
3. Configure DNS or use Netlify DNS

### Vercel
1. Go to Project settings → Domains
2. Add domain: `dsa-code.dev`
3. Configure DNS records as shown

## 🔒 Environment Variables

### Required Variables
```bash
REACT_APP_GITHUB_TOKEN=ghp_xxxxxxxxxxxxxxxxxxxx
REACT_APP_REPO_OWNER=Pradeepsingh61
REACT_APP_REPO_NAME=DSA_Code
```

### Optional Variables
```bash
REACT_APP_GA_TRACKING_ID=G-XXXXXXXXXX
REACT_APP_SENTRY_DSN=https://xxx@sentry.io/xxx
REACT_APP_API_BASE_URL=https://api.github.com
```

### Platform-Specific Setup

#### GitHub Actions
```yaml
# .github/workflows/deploy.yml
env:
  REACT_APP_GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
  REACT_APP_REPO_OWNER: Pradeepsingh61
  REACT_APP_REPO_NAME: DSA_Code
```

#### Netlify
```bash
# netlify.toml
[build.environment]
  REACT_APP_GITHUB_TOKEN = "ghp_xxxxxxxxxxxxxxxxxxxx"
  REACT_APP_REPO_OWNER = "Pradeepsingh61"
  REACT_APP_REPO_NAME = "DSA_Code"
```

#### Vercel
```json
// vercel.json
{
  "env": {
    "REACT_APP_GITHUB_TOKEN": "ghp_xxxxxxxxxxxxxxxxxxxx",
    "REACT_APP_REPO_OWNER": "Pradeepsingh61",
    "REACT_APP_REPO_NAME": "DSA_Code"
  }
}
```

## 📊 Performance Optimization

### Bundle Analysis
```bash
# Analyze bundle size
npm run build
npx webpack-bundle-analyzer build/static/js/*.js
```

### Optimization Checklist
- ✅ Code splitting implemented
- ✅ Images optimized and lazy loaded
- ✅ CSS minified and purged
- ✅ JavaScript minified
- ✅ Gzip compression enabled
- ✅ CDN for static assets
- ✅ Service worker for caching

### Performance Metrics
- **First Contentful Paint**: < 1.5s
- **Largest Contentful Paint**: < 2.5s
- **Cumulative Layout Shift**: < 0.1
- **First Input Delay**: < 100ms

## 🔍 SEO Configuration

### Meta Tags
```html
<!-- Automatically generated by React Helmet -->
<title>DSA Code - Data Structures & Algorithms Hub</title>
<meta name="description" content="Comprehensive collection of DSA implementations" />
<meta property="og:title" content="DSA Code" />
<meta property="og:description" content="Master Data Structures & Algorithms" />
```

### Sitemap Generation
```bash
# Generate sitemap after build
npm run build:sitemap
```

### Robots.txt
```
User-agent: *
Allow: /
Sitemap: https://dsa-code.dev/sitemap.xml
```

## 🚨 Troubleshooting

### Common Issues

#### Build Fails
```bash
# Clear cache and reinstall
rm -rf node_modules package-lock.json
npm install
npm run build
```

#### Routing Issues
- Ensure server redirects all routes to `index.html`
- Check `basename` prop in BrowserRouter

#### Environment Variables Not Working
- Ensure variables start with `REACT_APP_`
- Restart development server after adding variables
- Check platform-specific variable setup

#### GitHub API Rate Limiting
- Add GitHub token to environment variables
- Implement proper error handling
- Add request caching

### Debug Commands
```bash
# Check build output
npm run build && serve -s build

# Test production build locally
npx serve -s build -l 3000

# Check bundle size
npm run build && ls -la build/static/js/
```

## 📈 Monitoring

### Analytics Setup
```javascript
// Google Analytics 4
gtag('config', 'G-XXXXXXXXXX');

// Track page views
gtag('event', 'page_view', {
  page_title: document.title,
  page_location: window.location.href
});
```

### Error Tracking
```javascript
// Sentry integration
import * as Sentry from "@sentry/react";

Sentry.init({
  dsn: process.env.REACT_APP_SENTRY_DSN,
  environment: process.env.NODE_ENV
});
```

### Performance Monitoring
```javascript
// Web Vitals
import { getCLS, getFID, getFCP, getLCP, getTTFB } from 'web-vitals';

getCLS(console.log);
getFID(console.log);
getFCP(console.log);
getLCP(console.log);
getTTFB(console.log);
```

## 🔄 CI/CD Pipeline

### GitHub Actions Workflow
```yaml
name: Deploy to Production
on:
  push:
    branches: [main]
    paths: ['react-frontend/**']

jobs:
  deploy:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v3
      - uses: actions/setup-node@v3
        with:
          node-version: '18'
          cache: 'npm'
      - run: npm ci
      - run: npm run build
      - run: npm run test:ci
      - uses: peaceiris/actions-gh-pages@v3
        with:
          github_token: ${{ secrets.GITHUB_TOKEN }}
          publish_dir: ./build
```

### Deployment Checklist
- [ ] Environment variables configured
- [ ] Build passes successfully
- [ ] Tests pass
- [ ] Performance metrics acceptable
- [ ] SEO tags configured
- [ ] Error tracking setup
- [ ] Analytics configured
- [ ] Custom domain configured (if applicable)
- [ ] SSL certificate active
- [ ] CDN configured (if applicable)

---

**🎉 Your DSA Code React frontend is now ready for production deployment!**
