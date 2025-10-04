# Environment Configuration Guide

Complete guide for setting up environment variables and configuration for the DSA Code React frontend.

## 🔧 Environment Variables

### Required Variables

#### GitHub API Integration
```bash
# GitHub Personal Access Token (required for API calls)
REACT_APP_GITHUB_TOKEN=ghp_xxxxxxxxxxxxxxxxxxxx

# Repository Information
REACT_APP_REPO_OWNER=Pradeepsingh61
REACT_APP_REPO_NAME=DSA_Code
```

### Optional Variables

#### Application Configuration
```bash
# App Metadata
REACT_APP_APP_NAME="DSA Code"
REACT_APP_APP_VERSION="1.0.0"
REACT_APP_APP_DESCRIPTION="Comprehensive Data Structures and Algorithms Hub"

# API Configuration
REACT_APP_API_BASE_URL=https://api.github.com
REACT_APP_RAW_CONTENT_BASE_URL=https://raw.githubusercontent.com

# Feature Flags
REACT_APP_ENABLE_ANALYTICS=true
REACT_APP_ENABLE_ERROR_TRACKING=true
REACT_APP_ENABLE_PWA=true
```

#### Analytics & Monitoring
```bash
# Google Analytics 4
REACT_APP_GA_TRACKING_ID=G-XXXXXXXXXX

# Sentry Error Tracking
REACT_APP_SENTRY_DSN=https://xxxxx@sentry.io/xxxxx

# Performance Monitoring
REACT_APP_ENABLE_WEB_VITALS=true
```

## 📁 Environment Files

### Development (.env.development)
```bash
# Development environment
NODE_ENV=development
REACT_APP_GITHUB_TOKEN=ghp_dev_token_here
REACT_APP_REPO_OWNER=Pradeepsingh61
REACT_APP_REPO_NAME=DSA_Code
REACT_APP_API_BASE_URL=https://api.github.com
REACT_APP_ENABLE_ANALYTICS=false
REACT_APP_ENABLE_ERROR_TRACKING=false
```

### Production (.env.production)
```bash
# Production environment
NODE_ENV=production
REACT_APP_GITHUB_TOKEN=ghp_prod_token_here
REACT_APP_REPO_OWNER=Pradeepsingh61
REACT_APP_REPO_NAME=DSA_Code
REACT_APP_API_BASE_URL=https://api.github.com
REACT_APP_GA_TRACKING_ID=G-XXXXXXXXXX
REACT_APP_SENTRY_DSN=https://xxxxx@sentry.io/xxxxx
REACT_APP_ENABLE_ANALYTICS=true
REACT_APP_ENABLE_ERROR_TRACKING=true
```

### Local Development (.env.local)
```bash
# Local overrides (not committed to git)
REACT_APP_GITHUB_TOKEN=ghp_your_personal_token_here
REACT_APP_DEBUG_MODE=true
REACT_APP_MOCK_API=false
```

## 🔑 GitHub Token Setup

### Creating a GitHub Personal Access Token

1. **Go to GitHub Settings**
   - Navigate to https://github.com/settings/tokens
   - Click "Generate new token (classic)"

2. **Configure Token**
   - **Note**: "DSA Code Frontend Access"
   - **Expiration**: 90 days (or custom)
   - **Scopes**: Select the following:
     - `public_repo` - Access public repositories
     - `read:user` - Read user profile data
     - `read:org` - Read organization data

3. **Copy Token**
   - Copy the generated token (starts with `ghp_`)
   - Store it securely - you won't see it again!

4. **Add to Environment**
   ```bash
   REACT_APP_GITHUB_TOKEN=ghp_your_copied_token_here
   ```

### Token Security Best Practices

#### ✅ Do's
- Use different tokens for development and production
- Set appropriate expiration dates
- Use minimal required scopes
- Store tokens in environment variables
- Rotate tokens regularly

#### ❌ Don'ts
- Never commit tokens to git
- Don't use tokens with excessive permissions
- Don't share tokens between projects
- Don't hardcode tokens in source code

## 🌐 Platform-Specific Configuration

### GitHub Pages
```yaml
# .github/workflows/deploy.yml
env:
  REACT_APP_GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
  REACT_APP_REPO_OWNER: Pradeepsingh61
  REACT_APP_REPO_NAME: DSA_Code
  REACT_APP_GA_TRACKING_ID: ${{ secrets.GA_TRACKING_ID }}
```

### Netlify
```toml
# netlify.toml
[build.environment]
  REACT_APP_GITHUB_TOKEN = "ghp_xxxxxxxxxxxxxxxxxxxx"
  REACT_APP_REPO_OWNER = "Pradeepsingh61"
  REACT_APP_REPO_NAME = "DSA_Code"
  REACT_APP_GA_TRACKING_ID = "G-XXXXXXXXXX"

[context.production.environment]
  REACT_APP_ENABLE_ANALYTICS = "true"
  REACT_APP_ENABLE_ERROR_TRACKING = "true"

[context.deploy-preview.environment]
  REACT_APP_ENABLE_ANALYTICS = "false"
  REACT_APP_ENABLE_ERROR_TRACKING = "false"
```

### Vercel
```json
{
  "env": {
    "REACT_APP_GITHUB_TOKEN": "ghp_xxxxxxxxxxxxxxxxxxxx",
    "REACT_APP_REPO_OWNER": "Pradeepsingh61",
    "REACT_APP_REPO_NAME": "DSA_Code"
  },
  "build": {
    "env": {
      "REACT_APP_GA_TRACKING_ID": "@ga_tracking_id",
      "REACT_APP_SENTRY_DSN": "@sentry_dsn"
    }
  }
}
```

### Firebase
```json
{
  "hosting": {
    "public": "build",
    "rewrites": [
      {
        "source": "**",
        "destination": "/index.html"
      }
    ],
    "headers": [
      {
        "source": "/static/**",
        "headers": [
          {
            "key": "Cache-Control",
            "value": "public, max-age=31536000, immutable"
          }
        ]
      }
    ]
  }
}
```

## 🔍 Environment Validation

### Runtime Validation
```javascript
// src/utils/validateEnv.js
const requiredEnvVars = [
  'REACT_APP_GITHUB_TOKEN',
  'REACT_APP_REPO_OWNER',
  'REACT_APP_REPO_NAME'
];

export const validateEnvironment = () => {
  const missing = requiredEnvVars.filter(
    varName => !process.env[varName]
  );

  if (missing.length > 0) {
    console.error('Missing required environment variables:', missing);
    throw new Error(`Missing environment variables: ${missing.join(', ')}`);
  }

  // Validate GitHub token format
  const token = process.env.REACT_APP_GITHUB_TOKEN;
  if (!token.startsWith('ghp_')) {
    console.warn('GitHub token may be invalid format');
  }

  console.log('✅ Environment validation passed');
};
```

### Build-time Validation
```javascript
// scripts/validate-env.js
const fs = require('fs');
const path = require('path');

const envFile = path.join(__dirname, '../.env');
const requiredVars = [
  'REACT_APP_GITHUB_TOKEN',
  'REACT_APP_REPO_OWNER',
  'REACT_APP_REPO_NAME'
];

if (!fs.existsSync(envFile)) {
  console.error('❌ .env file not found');
  process.exit(1);
}

const envContent = fs.readFileSync(envFile, 'utf8');
const missingVars = requiredVars.filter(
  varName => !envContent.includes(varName)
);

if (missingVars.length > 0) {
  console.error('❌ Missing required variables:', missingVars);
  process.exit(1);
}

console.log('✅ Environment file validation passed');
```

## 🚨 Troubleshooting

### Common Issues

#### Environment Variables Not Loading
```bash
# Check if variables are properly prefixed
echo $REACT_APP_GITHUB_TOKEN

# Restart development server
npm start
```

#### GitHub API Rate Limiting
```javascript
// Check rate limit status
const response = await fetch('https://api.github.com/rate_limit', {
  headers: {
    'Authorization': `token ${process.env.REACT_APP_GITHUB_TOKEN}`
  }
});
const rateLimit = await response.json();
console.log('Rate limit:', rateLimit);
```

#### Token Authentication Errors
```javascript
// Test token validity
const testToken = async () => {
  try {
    const response = await fetch('https://api.github.com/user', {
      headers: {
        'Authorization': `token ${process.env.REACT_APP_GITHUB_TOKEN}`
      }
    });
    
    if (response.ok) {
      console.log('✅ Token is valid');
    } else {
      console.error('❌ Token is invalid');
    }
  } catch (error) {
    console.error('❌ Token test failed:', error);
  }
};
```

### Debug Commands
```bash
# Print all environment variables
npm run env

# Check specific variable
echo $REACT_APP_GITHUB_TOKEN

# Validate environment setup
npm run validate:env

# Test API connectivity
npm run test:api
```

## 🔒 Security Considerations

### Token Security
- **Scope Limitation**: Use minimal required scopes
- **Expiration**: Set reasonable expiration dates
- **Rotation**: Rotate tokens regularly
- **Monitoring**: Monitor token usage

### Environment Security
- **Separation**: Use different tokens for different environments
- **Access Control**: Limit who can access production tokens
- **Audit**: Regular security audits of environment setup
- **Backup**: Secure backup of environment configurations

### Client-Side Considerations
```javascript
// ⚠️ Remember: All REACT_APP_ variables are exposed to the client
// Never put sensitive data in REACT_APP_ variables

// ✅ Safe for client-side
REACT_APP_API_BASE_URL=https://api.github.com
REACT_APP_REPO_OWNER=Pradeepsingh61

// ❌ Never do this (sensitive data)
REACT_APP_DATABASE_PASSWORD=secret123
REACT_APP_PRIVATE_KEY=private_key_here
```

## 📊 Environment Monitoring

### Health Checks
```javascript
// src/utils/healthCheck.js
export const performHealthCheck = async () => {
  const checks = {
    githubApi: false,
    environment: false,
    dependencies: false
  };

  // Check GitHub API
  try {
    const response = await fetch('https://api.github.com/rate_limit');
    checks.githubApi = response.ok;
  } catch (error) {
    console.error('GitHub API health check failed:', error);
  }

  // Check environment variables
  checks.environment = !![
    process.env.REACT_APP_GITHUB_TOKEN,
    process.env.REACT_APP_REPO_OWNER,
    process.env.REACT_APP_REPO_NAME
  ].every(Boolean);

  return checks;
};
```

### Environment Info Component
```javascript
// src/components/EnvironmentInfo.js (development only)
const EnvironmentInfo = () => {
  if (process.env.NODE_ENV !== 'development') return null;

  return (
    <div style={{ position: 'fixed', bottom: 0, right: 0, background: '#000', color: '#fff', padding: '10px' }}>
      <div>Environment: {process.env.NODE_ENV}</div>
      <div>API: {process.env.REACT_APP_API_BASE_URL}</div>
      <div>Token: {process.env.REACT_APP_GITHUB_TOKEN ? '✅' : '❌'}</div>
    </div>
  );
};
```

---

**🔧 Your environment is now properly configured for the DSA Code React frontend!**

## Quick Setup Checklist
- [ ] Copy `.env.example` to `.env`
- [ ] Generate GitHub Personal Access Token
- [ ] Add token to `.env` file
- [ ] Configure platform-specific variables
- [ ] Test API connectivity
- [ ] Validate environment setup
- [ ] Deploy with proper environment variables
