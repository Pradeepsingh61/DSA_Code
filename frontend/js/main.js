// Main JavaScript for DSA Code Frontend
class DSACodeApp {
    constructor() {
        this.currentSection = 'home';
        this.theme = localStorage.getItem('theme') || 'light';
        this.algorithms = [];
        this.dataStructures = [];
        
        this.init();
    }

    init() {
        this.setupTheme();
        this.setupNavigation();
        this.setupLoadingScreen();
        this.setupScrollEffects();
        this.setupSearch();
        this.setupAnimations();
        this.loadData();
        this.setupHeroCode();
    }

    setupTheme() {
        document.documentElement.setAttribute('data-theme', this.theme);
        const themeToggle = document.getElementById('theme-toggle');
        const icon = themeToggle.querySelector('i');
        
        icon.className = this.theme === 'dark' ? 'fas fa-sun' : 'fas fa-moon';
        
        themeToggle.addEventListener('click', () => {
            this.theme = this.theme === 'light' ? 'dark' : 'light';
            document.documentElement.setAttribute('data-theme', this.theme);
            localStorage.setItem('theme', this.theme);
            icon.className = this.theme === 'dark' ? 'fas fa-sun' : 'fas fa-moon';
        });
    }

    setupNavigation() {
        const navLinks = document.querySelectorAll('.nav-link');
        const sections = document.querySelectorAll('.section, .hero-section');
        
        navLinks.forEach(link => {
            link.addEventListener('click', (e) => {
                e.preventDefault();
                const targetSection = link.getAttribute('data-section');
                this.navigateToSection(targetSection);
            });
        });

        // Handle button navigation
        document.addEventListener('click', (e) => {
            if (e.target.hasAttribute('data-section')) {
                const targetSection = e.target.getAttribute('data-section');
                this.navigateToSection(targetSection);
            }
        });
    }

    navigateToSection(sectionName) {
        // Update active nav link
        document.querySelectorAll('.nav-link').forEach(link => {
            link.classList.remove('active');
            if (link.getAttribute('data-section') === sectionName) {
                link.classList.add('active');
            }
        });

        // Show target section
        document.querySelectorAll('.section, .hero-section').forEach(section => {
            section.classList.remove('active-section');
            if (section.id === sectionName) {
                section.classList.add('active-section');
            }
        });

        this.currentSection = sectionName;
        
        // Scroll to top
        window.scrollTo({ top: 0, behavior: 'smooth' });
    }

    setupLoadingScreen() {
        window.addEventListener('load', () => {
            setTimeout(() => {
                const loadingScreen = document.getElementById('loading-screen');
                loadingScreen.classList.add('hidden');
                
                setTimeout(() => {
                    loadingScreen.style.display = 'none';
                }, 500);
            }, 1500);
        });
    }

    setupScrollEffects() {
        const navbar = document.getElementById('navbar');
        const backToTop = document.getElementById('back-to-top');
        
        window.addEventListener('scroll', () => {
            const scrollY = window.scrollY;
            
            // Navbar background opacity
            if (scrollY > 50) {
                navbar.style.background = this.theme === 'dark' 
                    ? 'rgba(15, 23, 42, 0.98)' 
                    : 'rgba(255, 255, 255, 0.98)';
            } else {
                navbar.style.background = this.theme === 'dark' 
                    ? 'rgba(15, 23, 42, 0.95)' 
                    : 'rgba(255, 255, 255, 0.95)';
            }
            
            // Back to top button
            if (scrollY > 300) {
                backToTop.classList.add('visible');
            } else {
                backToTop.classList.remove('visible');
            }
        });

        if (backToTop) {
            backToTop.addEventListener('click', () => {
                window.scrollTo({ top: 0, behavior: 'smooth' });
            });
        }
    }

    setupSearch() {
        const searchInput = document.getElementById('algorithm-search');
        const filterTabs = document.querySelectorAll('.filter-tab');
        
        if (searchInput) {
            searchInput.addEventListener('input', (e) => {
                this.filterAlgorithms(e.target.value);
            });
        }

        filterTabs.forEach(tab => {
            tab.addEventListener('click', () => {
                filterTabs.forEach(t => t.classList.remove('active'));
                tab.classList.add('active');
                
                const category = tab.getAttribute('data-category');
                this.filterByCategory(category);
            });
        });
    }

    setupAnimations() {
        // Counter animation for hero stats
        const observerOptions = {
            threshold: 0.5,
            rootMargin: '0px 0px -100px 0px'
        };

        const observer = new IntersectionObserver((entries) => {
            entries.forEach(entry => {
                if (entry.isIntersecting) {
                    this.animateCounters();
                    observer.unobserve(entry.target);
                }
            });
        }, observerOptions);

        const heroSection = document.getElementById('home');
        if (heroSection) {
            observer.observe(heroSection);
        }

        // Fade in animation for cards
        const cardObserver = new IntersectionObserver((entries) => {
            entries.forEach(entry => {
                if (entry.isIntersecting) {
                    entry.target.classList.add('fade-in-up');
                }
            });
        }, { threshold: 0.1 });

        // Observe cards when they're created
        this.observeCards = (cards) => {
            cards.forEach(card => cardObserver.observe(card));
        };
    }

    animateCounters() {
        const counters = document.querySelectorAll('.stat-number');
        
        counters.forEach(counter => {
            const target = parseInt(counter.getAttribute('data-count'));
            const duration = 2000;
            const step = target / (duration / 16);
            let current = 0;
            
            const timer = setInterval(() => {
                current += step;
                if (current >= target) {
                    counter.textContent = target.toLocaleString();
                    clearInterval(timer);
                } else {
                    counter.textContent = Math.floor(current).toLocaleString();
                }
            }, 16);
        });
    }

    setupHeroCode() {
        const heroCode = document.getElementById('hero-code');
        if (heroCode) {
            const codeSnippet = `public class FenwickTree {
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
            
            this.typeWriter(heroCode, codeSnippet, 30);
        }
    }

    typeWriter(element, text, speed) {
        let i = 0;
        element.textContent = '';
        
        const timer = setInterval(() => {
            if (i < text.length) {
                element.textContent += text.charAt(i);
                i++;
            } else {
                clearInterval(timer);
            }
        }, speed);
    }

    loadData() {
        // Load algorithms data
        this.algorithms = [
            {
                name: 'Fenwick Tree',
                category: 'data-structures',
                language: 'Java',
                difficulty: 'Medium',
                description: 'Binary Indexed Tree for efficient range sum queries',
                timeComplexity: 'O(log n)',
                spaceComplexity: 'O(n)',
                path: 'Java/data_structures/trees/FenwickTree.java'
            },
            {
                name: 'Matrix Multiplication',
                category: 'mathematical',
                language: 'Java',
                difficulty: 'Medium',
                description: 'Efficient matrix multiplication algorithm',
                timeComplexity: 'O(m×n×p)',
                spaceComplexity: 'O(m×p)',
                path: 'Java/algorithms/matrix/MatrixMultiplication.java'
            },
            {
                name: 'Quick Sort',
                category: 'sorting',
                language: 'Java',
                difficulty: 'Medium',
                description: 'Efficient divide-and-conquer sorting algorithm',
                timeComplexity: 'O(n log n)',
                spaceComplexity: 'O(log n)',
                path: 'Java/algorithms/sorting/QuickSort.java'
            },
            {
                name: 'Binary Search',
                category: 'searching',
                language: 'Java',
                difficulty: 'Easy',
                description: 'Efficient search algorithm for sorted arrays',
                timeComplexity: 'O(log n)',
                spaceComplexity: 'O(1)',
                path: 'Java/algorithms/BinarySearch.java'
            },
            {
                name: 'Dijkstra Algorithm',
                category: 'graph',
                language: 'Java',
                difficulty: 'Hard',
                description: 'Shortest path algorithm for weighted graphs',
                timeComplexity: 'O((V + E) log V)',
                spaceComplexity: 'O(V)',
                path: 'Java/algorithms/graph_algorithms/DijkstraAlgorithm.java'
            },
            {
                name: 'A* Search',
                category: 'graph',
                language: 'Java',
                difficulty: 'Hard',
                description: 'Heuristic pathfinding algorithm',
                timeComplexity: 'O(b^d)',
                spaceComplexity: 'O(b^d)',
                path: 'Java/algorithms/graph_algorithms/AStarSearch.java'
            }
        ];

        this.dataStructures = [
            {
                name: 'Fenwick Tree',
                language: 'Java',
                difficulty: 'Medium',
                description: 'Binary Indexed Tree for range queries',
                operations: ['update', 'query', 'prefixSum'],
                path: 'Java/data_structures/trees/FenwickTree.java'
            },
            {
                name: 'Trie',
                language: 'Java',
                difficulty: 'Medium',
                description: 'Prefix tree for string operations',
                operations: ['insert', 'search', 'startsWith'],
                path: 'Java/data_structures/trees/Trie.java'
            }
        ];

        this.renderAlgorithms();
        this.renderDataStructures();
    }

    renderAlgorithms() {
        const grid = document.getElementById('algorithms-grid');
        if (!grid) return;

        grid.innerHTML = '';
        
        this.algorithms.forEach(algorithm => {
            const card = this.createAlgorithmCard(algorithm);
            grid.appendChild(card);
        });

        this.observeCards(grid.children);
    }

    renderDataStructures() {
        const grid = document.getElementById('data-structures-grid');
        if (!grid) return;

        grid.innerHTML = '';
        
        this.dataStructures.forEach(ds => {
            const card = this.createDataStructureCard(ds);
            grid.appendChild(card);
        });

        this.observeCards(grid.children);
    }

    createAlgorithmCard(algorithm) {
        const card = document.createElement('div');
        card.className = 'algorithm-card';
        card.innerHTML = `
            <div class="card-header">
                <h3 class="card-title">${algorithm.name}</h3>
                <span class="difficulty-badge ${algorithm.difficulty.toLowerCase()}">${algorithm.difficulty}</span>
            </div>
            <p class="card-description">${algorithm.description}</p>
            <div class="card-meta">
                <div class="meta-item">
                    <i class="fas fa-clock"></i>
                    <span>Time: ${algorithm.timeComplexity}</span>
                </div>
                <div class="meta-item">
                    <i class="fas fa-memory"></i>
                    <span>Space: ${algorithm.spaceComplexity}</span>
                </div>
                <div class="meta-item">
                    <i class="fas fa-code"></i>
                    <span>${algorithm.language}</span>
                </div>
            </div>
            <div class="card-actions">
                <button class="btn-view-code" data-path="${algorithm.path}">
                    <i class="fas fa-code"></i>
                    View Code
                </button>
                <button class="btn-github" data-path="${algorithm.path}">
                    <i class="fab fa-github"></i>
                    GitHub
                </button>
            </div>
        `;

        // Add click handlers
        card.querySelector('.btn-view-code').addEventListener('click', () => {
            this.viewCode(algorithm.path);
        });

        card.querySelector('.btn-github').addEventListener('click', () => {
            window.open(`https://github.com/Pradeepsingh61/DSA_Code/blob/main/${algorithm.path}`, '_blank');
        });

        return card;
    }

    createDataStructureCard(ds) {
        const card = document.createElement('div');
        card.className = 'data-structure-card';
        card.innerHTML = `
            <div class="card-header">
                <h3 class="card-title">${ds.name}</h3>
                <span class="difficulty-badge ${ds.difficulty.toLowerCase()}">${ds.difficulty}</span>
            </div>
            <p class="card-description">${ds.description}</p>
            <div class="operations-list">
                <h4>Operations:</h4>
                <div class="operations">
                    ${ds.operations.map(op => `<span class="operation-tag">${op}</span>`).join('')}
                </div>
            </div>
            <div class="card-actions">
                <button class="btn-view-code" data-path="${ds.path}">
                    <i class="fas fa-code"></i>
                    View Code
                </button>
                <button class="btn-github" data-path="${ds.path}">
                    <i class="fab fa-github"></i>
                    GitHub
                </button>
            </div>
        `;

        // Add click handlers
        card.querySelector('.btn-view-code').addEventListener('click', () => {
            this.viewCode(ds.path);
        });

        card.querySelector('.btn-github').addEventListener('click', () => {
            window.open(`https://github.com/Pradeepsingh61/DSA_Code/blob/main/${ds.path}`, '_blank');
        });

        return card;
    }

    filterAlgorithms(searchTerm) {
        const cards = document.querySelectorAll('.algorithm-card');
        
        cards.forEach(card => {
            const title = card.querySelector('.card-title').textContent.toLowerCase();
            const description = card.querySelector('.card-description').textContent.toLowerCase();
            
            if (title.includes(searchTerm.toLowerCase()) || description.includes(searchTerm.toLowerCase())) {
                card.style.display = 'block';
            } else {
                card.style.display = 'none';
            }
        });
    }

    filterByCategory(category) {
        const cards = document.querySelectorAll('.algorithm-card');
        
        cards.forEach(card => {
            if (category === 'all') {
                card.style.display = 'block';
            } else {
                // This would need to be implemented based on algorithm categories
                card.style.display = 'block';
            }
        });
    }

    viewCode(path) {
        // Create modal to show code
        const modal = document.createElement('div');
        modal.className = 'code-modal';
        modal.innerHTML = `
            <div class="modal-content">
                <div class="modal-header">
                    <h3>${path}</h3>
                    <button class="modal-close">&times;</button>
                </div>
                <div class="modal-body">
                    <pre><code>Loading code...</code></pre>
                </div>
            </div>
        `;

        document.body.appendChild(modal);

        // Close modal functionality
        modal.querySelector('.modal-close').addEventListener('click', () => {
            document.body.removeChild(modal);
        });

        modal.addEventListener('click', (e) => {
            if (e.target === modal) {
                document.body.removeChild(modal);
            }
        });

        // In a real implementation, you would fetch the actual code
        setTimeout(() => {
            modal.querySelector('code').textContent = `// Code for ${path}\n// This would contain the actual implementation`;
        }, 500);
    }
}

// Initialize the app when DOM is loaded
document.addEventListener('DOMContentLoaded', () => {
    new DSACodeApp();
});

// Add some additional CSS for the components
const additionalCSS = `
.card-header {
    display: flex;
    justify-content: space-between;
    align-items: center;
    margin-bottom: 1rem;
}

.card-title {
    font-size: 1.25rem;
    font-weight: 600;
    color: var(--text-primary);
}

.difficulty-badge {
    padding: 0.25rem 0.75rem;
    border-radius: var(--radius-sm);
    font-size: 0.75rem;
    font-weight: 600;
    text-transform: uppercase;
}

.difficulty-badge.easy {
    background-color: rgba(16, 185, 129, 0.1);
    color: var(--secondary-color);
}

.difficulty-badge.medium {
    background-color: rgba(245, 158, 11, 0.1);
    color: var(--accent-color);
}

.difficulty-badge.hard {
    background-color: rgba(239, 68, 68, 0.1);
    color: var(--danger-color);
}

.card-description {
    color: var(--text-secondary);
    margin-bottom: 1.5rem;
    line-height: 1.6;
}

.card-meta {
    display: flex;
    flex-direction: column;
    gap: 0.5rem;
    margin-bottom: 1.5rem;
}

.meta-item {
    display: flex;
    align-items: center;
    gap: 0.5rem;
    font-size: 0.9rem;
    color: var(--text-secondary);
}

.meta-item i {
    width: 16px;
    color: var(--primary-color);
}

.card-actions {
    display: flex;
    gap: 0.75rem;
}

.btn-view-code,
.btn-github {
    flex: 1;
    display: flex;
    align-items: center;
    justify-content: center;
    gap: 0.5rem;
    padding: 0.75rem;
    border: none;
    border-radius: var(--radius-md);
    font-weight: 500;
    cursor: pointer;
    transition: all var(--transition-fast);
}

.btn-view-code {
    background-color: var(--primary-color);
    color: white;
}

.btn-view-code:hover {
    background-color: var(--primary-dark);
    transform: translateY(-2px);
}

.btn-github {
    background-color: var(--bg-tertiary);
    color: var(--text-primary);
}

.btn-github:hover {
    background-color: var(--text-primary);
    color: var(--text-inverse);
}

.operations-list {
    margin-bottom: 1.5rem;
}

.operations-list h4 {
    font-size: 0.9rem;
    color: var(--text-secondary);
    margin-bottom: 0.5rem;
}

.operations {
    display: flex;
    flex-wrap: wrap;
    gap: 0.5rem;
}

.operation-tag {
    padding: 0.25rem 0.75rem;
    background-color: rgba(99, 102, 241, 0.1);
    color: var(--primary-color);
    border-radius: var(--radius-sm);
    font-size: 0.8rem;
    font-weight: 500;
}

.code-modal {
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background-color: var(--bg-overlay);
    display: flex;
    align-items: center;
    justify-content: center;
    z-index: 10000;
}

.modal-content {
    background-color: var(--bg-card);
    border-radius: var(--radius-lg);
    max-width: 90vw;
    max-height: 90vh;
    overflow: hidden;
    box-shadow: var(--shadow-xl);
}

.modal-header {
    padding: 1.5rem;
    border-bottom: 1px solid var(--border-color);
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.modal-close {
    background: none;
    border: none;
    font-size: 1.5rem;
    cursor: pointer;
    color: var(--text-secondary);
}

.modal-body {
    padding: 1.5rem;
    overflow: auto;
    max-height: 70vh;
}

.modal-body pre {
    font-family: var(--font-mono);
    background-color: var(--bg-tertiary);
    padding: 1rem;
    border-radius: var(--radius-md);
    overflow-x: auto;
}

.back-to-top {
    position: fixed;
    bottom: 2rem;
    right: 2rem;
    width: 50px;
    height: 50px;
    background-color: var(--primary-color);
    color: white;
    border: none;
    border-radius: 50%;
    cursor: pointer;
    opacity: 0;
    visibility: hidden;
    transition: all var(--transition-normal);
    z-index: 1000;
}

.back-to-top.visible {
    opacity: 1;
    visibility: visible;
}

.back-to-top:hover {
    background-color: var(--primary-dark);
    transform: translateY(-3px);
}
`;

// Inject additional CSS
const style = document.createElement('style');
style.textContent = additionalCSS;
document.head.appendChild(style);
