import React, { useEffect } from 'react';
import { Prism as SyntaxHighlighter } from 'react-syntax-highlighter';
import { vscDarkPlus } from 'react-syntax-highlighter/dist/esm/styles/prism';
import { Copy, ExternalLink } from 'lucide-react';
import toast from 'react-hot-toast';

const CodeWindow = ({ 
  title = 'Code', 
  language = 'javascript', 
  code = '', 
  githubUrl = null,
  showControls = true 
}) => {
  const copyToClipboard = async () => {
    try {
      await navigator.clipboard.writeText(code);
      toast.success('Code copied to clipboard!');
    } catch (err) {
      toast.error('Failed to copy code');
    }
  };

  const openInGitHub = () => {
    if (githubUrl) {
      window.open(githubUrl, '_blank', 'noopener,noreferrer');
    }
  };

  return (
    <div className="code-window">
      <div className="window-header">
        <div className="window-controls">
          <span className="control close"></span>
          <span className="control minimize"></span>
          <span className="control maximize"></span>
        </div>
        <div className="window-title">{title}</div>
        {showControls && (
          <div className="window-actions">
            <button 
              onClick={copyToClipboard}
              className="action-btn"
              title="Copy code"
            >
              <Copy size={16} />
            </button>
            {githubUrl && (
              <button 
                onClick={openInGitHub}
                className="action-btn"
                title="View on GitHub"
              >
                <ExternalLink size={16} />
              </button>
            )}
          </div>
        )}
      </div>
      <div className="code-content">
        <SyntaxHighlighter
          language={language}
          style={vscDarkPlus}
          customStyle={{
            margin: 0,
            padding: '1.5rem',
            background: 'transparent',
            fontSize: '0.9rem',
            lineHeight: '1.6'
          }}
          showLineNumbers={true}
          wrapLines={true}
        >
          {code}
        </SyntaxHighlighter>
      </div>

      <style jsx>{`
        .code-window {
          background-color: var(--bg-card);
          border-radius: var(--radius-xl);
          box-shadow: var(--shadow-xl);
          overflow: hidden;
          border: 1px solid var(--border-color);
          max-height: 500px;
          display: flex;
          flex-direction: column;
        }

        .window-header {
          background-color: var(--bg-tertiary);
          padding: 1rem 1.5rem;
          display: flex;
          align-items: center;
          justify-content: space-between;
          border-bottom: 1px solid var(--border-color);
        }

        .window-controls {
          display: flex;
          gap: 0.5rem;
        }

        .control {
          width: 12px;
          height: 12px;
          border-radius: 50%;
        }

        .control.close { 
          background-color: #ff5f57; 
        }
        
        .control.minimize { 
          background-color: #ffbd2e; 
        }
        
        .control.maximize { 
          background-color: #28ca42; 
        }

        .window-title {
          font-family: var(--font-mono);
          font-size: 0.9rem;
          color: var(--text-secondary);
          font-weight: 500;
        }

        .window-actions {
          display: flex;
          gap: 0.5rem;
        }

        .action-btn {
          background: none;
          border: none;
          color: var(--text-secondary);
          cursor: pointer;
          padding: 0.25rem;
          border-radius: var(--radius-sm);
          transition: all var(--transition-fast);
        }

        .action-btn:hover {
          color: var(--primary-color);
          background-color: rgba(99, 102, 241, 0.1);
        }

        .code-content {
          flex: 1;
          overflow: auto;
          background-color: #1e293b;
        }

        .code-content :global(.token.comment) {
          color: #64748b;
        }

        .code-content :global(.token.keyword) {
          color: #8b5cf6;
        }

        .code-content :global(.token.string) {
          color: #10b981;
        }

        .code-content :global(.token.number) {
          color: #f59e0b;
        }

        .code-content :global(.token.function) {
          color: #3b82f6;
        }

        .code-content :global(.token.class-name) {
          color: #f97316;
        }

        @media (max-width: 768px) {
          .code-window {
            max-height: 400px;
          }

          .window-header {
            padding: 0.75rem 1rem;
          }

          .window-title {
            font-size: 0.8rem;
          }

          .code-content :global(pre) {
            font-size: 0.8rem !important;
            padding: 1rem !important;
          }
        }
      `}</style>
    </div>
  );
};

export default CodeWindow;
