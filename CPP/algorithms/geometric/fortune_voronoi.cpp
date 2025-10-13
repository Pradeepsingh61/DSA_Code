/**
 * Fortune's Algorithm for Voronoi Diagram Construction
 * 
 * Purpose:
 * Computes the Voronoi diagram of a set of points in a plane. A Voronoi diagram
 * partitions the plane into regions, where each region contains all points closest
 * to a specific site (input point) than to any other site.
 * 
 * Time Complexity: O(n log n) where n is the number of input points
 * Space Complexity: O(n)
 * 
 * Author: Abhiram
 * Date: October 13, 2025
 */

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>
#include <algorithm>
#include <limits>

// Epsilon value for floating point comparisons
const double EPSILON = 1e-9;

// 2D Point structure
struct Point {
    double x, y;
    
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    
    // Compare points lexicographically
    bool operator<(const Point& other) const {
        if (std::abs(x - other.x) < EPSILON)
            return y < other.y;
        return x < other.x;
    }
    
    bool operator==(const Point& other) const {
        return std::abs(x - other.x) < EPSILON && std::abs(y - other.y) < EPSILON;
    }
};

// Line segment between two points
struct Edge {
    Point start, end;
    
    Edge(Point start = Point(), Point end = Point()) : start(start), end(end) {}
};

// Structure to represent a parabola in the beach line
struct Parabola {
    Point focus;        // Focus point (site)
    double directrix;   // y-coordinate of the directrix
    
    Parabola(Point focus = Point(), double directrix = 0) : focus(focus), directrix(directrix) {}
    
    // Calculate y-coordinate of the parabola at a given x
    double getY(double x) const {
        if (std::abs(focus.y - directrix) < EPSILON) {
            return std::numeric_limits<double>::infinity();
        }
        
        // Formula for parabola: y = ((x-h)^2 / (4*(p-d))) + (p+d)/2
        // where (h,p) is the focus and d is the directrix
        double h = focus.x;
        double p = focus.y;
        double d = directrix;
        
        return ((x - h) * (x - h) / (4 * (p - d))) + (p + d) / 2;
    }
};

// Site event (when the sweep line encounters a new site)
struct SiteEvent {
    Point point;
    
    SiteEvent(Point p) : point(p) {}
    
    // Compare site events by y-coordinate (descending)
    bool operator<(const SiteEvent& other) const {
        if (std::abs(point.y - other.point.y) < EPSILON)
            return point.x > other.point.x;
        return point.y < other.point.y;
    }
};

// Circle event (when the sweep line encounters a breakpoint disappearance)
struct CircleEvent {
    Point center;       // Center of the circle
    double y;           // y-coordinate where the event happens
    Point convergence;  // Point where the three arcs meet
    
    CircleEvent(Point center, double y, Point convergence)
        : center(center), y(y), convergence(convergence) {}
    
    // Compare circle events by y-coordinate
    bool operator<(const CircleEvent& other) const {
        return y < other.y;
    }
};

// Arc in the beach line
struct Arc {
    Parabola parabola;
    Arc *prev, *next;  // Pointers to prev and next arcs in the beach line
    Edge *edge;        // Edge created at the breakpoint with the next arc
    CircleEvent *circleEvent;  // Circle event where this arc disappears
    
    Arc(Parabola p) : parabola(p), prev(nullptr), next(nullptr), 
                     edge(nullptr), circleEvent(nullptr) {}
};

class FortuneAlgorithm {
private:
    std::vector<Point> sites;         // Input points
    std::vector<Edge> edges;          // Resulting Voronoi edges
    std::priority_queue<SiteEvent> siteEvents;
    std::priority_queue<CircleEvent> circleEvents;
    Arc* beachLineRoot;               // Root of the beach line tree
    double sweepLineY;                // Current position of sweep line
    
    // Initialize the algorithm with the input sites
    void initialize() {
        // Sort sites by y-coordinate (descending)
        for (const auto& site : sites) {
            siteEvents.push(SiteEvent(site));
        }
        
        beachLineRoot = nullptr;
        sweepLineY = std::numeric_limits<double>::infinity();
    }
    
    // Handle a site event
    void handleSiteEvent(const SiteEvent& event) {
        // Update sweep line position
        sweepLineY = event.point.y;
        
        if (beachLineRoot == nullptr) {
            // First site, just create a beach line with one arc
            beachLineRoot = new Arc(Parabola(event.point, sweepLineY));
            return;
        }
        
        // Find the arc above the new site
        Arc* arcAbove = findArcAbove(event.point.x);
        
        // Check if there's a circle event involving this arc and remove it
        if (arcAbove->circleEvent != nullptr) {
            // Invalid circle event
            arcAbove->circleEvent = nullptr;
        }
        
        // Split the arc
        Arc* leftArc = new Arc(arcAbove->parabola);
        Arc* middleArc = new Arc(Parabola(event.point, sweepLineY));
        Arc* rightArc = new Arc(arcAbove->parabola);
        
        // Update beach line structure
        middleArc->prev = leftArc;
        middleArc->next = rightArc;
        leftArc->next = middleArc;
        rightArc->prev = middleArc;
        
        // Update connections in the beach line
        if (arcAbove->prev != nullptr) {
            arcAbove->prev->next = leftArc;
            leftArc->prev = arcAbove->prev;
        }
        else {
            beachLineRoot = leftArc;
        }
        
        if (arcAbove->next != nullptr) {
            arcAbove->next->prev = rightArc;
            rightArc->next = arcAbove->next;
        }
        
        // Create new edges
        Edge* leftEdge = new Edge();
        Edge* rightEdge = new Edge();
        
        // Set up the edges
        leftArc->edge = leftEdge;
        middleArc->edge = rightEdge;
        
        // Add new edges to the result
        edges.push_back(*leftEdge);
        edges.push_back(*rightEdge);
        
        // Check for new circle events
        checkCircleEvent(leftArc);
        checkCircleEvent(rightArc);
        
        // Clean up
        delete arcAbove;
    }
    
    // Handle a circle event
    void handleCircleEvent(const CircleEvent& event) {
        // Update sweep line position
        sweepLineY = event.y;
        
        // Find the arc that will disappear
        Arc* arc = findArcByCircleEvent(event);
        
        if (arc == nullptr) {
            return; // Invalid circle event
        }
        
        // Get the arcs to the left and right
        Arc* leftArc = arc->prev;
        Arc* rightArc = arc->next;
        
        // Create a new edge at the convergence point
        Edge* newEdge = new Edge();
        newEdge->start = event.convergence;
        
        // Add the new edge to the result
        edges.push_back(*newEdge);
        
        // Connect the new edge to existing edges
        if (leftArc->edge) leftArc->edge->end = event.convergence;
        if (rightArc->edge) rightArc->edge->end = event.convergence;
        
        // Update beach line
        leftArc->next = rightArc;
        rightArc->prev = leftArc;
        
        // Check for new circle events
        checkCircleEvent(leftArc);
        checkCircleEvent(rightArc);
        
        // Clean up
        delete arc;
    }
    
    // Find the arc in the beach line above a given x-coordinate
    Arc* findArcAbove(double x) {
        Arc* current = beachLineRoot;
        
        while (current != nullptr) {
            double breakpointLeft = -std::numeric_limits<double>::infinity();
            double breakpointRight = std::numeric_limits<double>::infinity();
            
            if (current->prev != nullptr) {
                breakpointLeft = computeBreakpoint(
                    current->prev->parabola.focus,
                    current->parabola.focus,
                    sweepLineY
                );
            }
            
            if (current->next != nullptr) {
                breakpointRight = computeBreakpoint(
                    current->parabola.focus,
                    current->next->parabola.focus,
                    sweepLineY
                );
            }
            
            if (x < breakpointLeft) {
                current = current->prev;
            }
            else if (x > breakpointRight) {
                current = current->next;
            }
            else {
                return current;
            }
        }
        
        // Should never happen if beach line is properly set up
        return beachLineRoot;
    }
    
    // Compute the x-coordinate of the breakpoint between two arcs
    double computeBreakpoint(const Point& focus1, const Point& focus2, double directrix) {
        // Handle special cases
        if (std::abs(focus1.y - focus2.y) < EPSILON) {
            return (focus1.x + focus2.x) / 2;
        }
        
        // Parameters for the two parabolas
        double h1 = focus1.x;
        double k1 = focus1.y;
        double h2 = focus2.x;
        double k2 = focus2.y;
        double d = directrix;
        
        // Compute quadratic equation coefficients
        double a = k1 - k2;
        double b = 2 * (h2 * (k1 - d) - h1 * (k2 - d));
        double c = (k1 - d) * (h2 * h2 + d * d - 2 * d * k2) -
                   (k2 - d) * (h1 * h1 + d * d - 2 * d * k1);
        
        // Solve the quadratic equation
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0) {
            // Should not happen, but just in case
            return (h1 + h2) / 2;
        }
        
        double x1 = (-b + std::sqrt(discriminant)) / (2 * a);
        double x2 = (-b - std::sqrt(discriminant)) / (2 * a);
        
        // Return the correct root based on the relative positions
        if (k1 > k2) {
            return std::max(x1, x2);
        } else {
            return std::min(x1, x2);
        }
    }
    
    // Check if a triple of consecutive arcs forms a circle event
    void checkCircleEvent(Arc* arc) {
        if (arc == nullptr || arc->prev == nullptr || arc->next == nullptr) {
            return;
        }
        
        Point focus1 = arc->prev->parabola.focus;
        Point focus2 = arc->parabola.focus;
        Point focus3 = arc->next->parabola.focus;
        
        // Check if the three points are nearly collinear
        double area = (focus1.x * (focus2.y - focus3.y) +
                      focus2.x * (focus3.y - focus1.y) +
                      focus3.x * (focus1.y - focus2.y)) / 2.0;
        
        if (std::abs(area) < EPSILON) {
            return; // Points are collinear, no circle event
        }
        
        // Calculate the center and radius of the circle through the three points
        Point center = calculateCircleCenter(focus1, focus2, focus3);
        double radius = std::sqrt(std::pow(center.x - focus1.x, 2) + 
                                std::pow(center.y - focus1.y, 2));
        
        // Calculate the y-coordinate of the bottom of the circle
        double bottomY = center.y - radius;
        
        // Create circle event only if the circle is below the sweep line
        if (bottomY < sweepLineY) {
            CircleEvent circleEvent(center, bottomY, Point(center.x, bottomY));
            arc->circleEvent = new CircleEvent(circleEvent);
            circleEvents.push(circleEvent);
        }
    }
    
    // Calculate the center of the circle through three points
    Point calculateCircleCenter(const Point& p1, const Point& p2, const Point& p3) {
        // Using the perpendicular bisector method
        double d = 2 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
        
        double ux = ((p1.x * p1.x + p1.y * p1.y) * (p2.y - p3.y) +
                    (p2.x * p2.x + p2.y * p2.y) * (p3.y - p1.y) +
                    (p3.x * p3.x + p3.y * p3.y) * (p1.y - p2.y)) / d;
                    
        double uy = ((p1.x * p1.x + p1.y * p1.y) * (p3.x - p2.x) +
                    (p2.x * p2.x + p2.y * p2.y) * (p1.x - p3.x) +
                    (p3.x * p3.x + p3.y * p3.y) * (p2.x - p1.x)) / d;
                    
        return Point(ux, uy);
    }
    
    // Find an arc by its associated circle event
    Arc* findArcByCircleEvent(const CircleEvent& event) {
        Arc* current = beachLineRoot;
        
        while (current != nullptr) {
            if (current->circleEvent && 
                std::abs(current->circleEvent->center.x - event.center.x) < EPSILON && 
                std::abs(current->circleEvent->center.y - event.center.y) < EPSILON) {
                return current;
            }
            current = current->next;
        }
        
        return nullptr;
    }
    
    // Clean up the beach line
    void cleanupBeachLine(Arc* arc) {
        if (arc == nullptr) {
            return;
        }
        
        cleanupBeachLine(arc->next);
        delete arc;
    }

    // Calculate the bounding box of the sites
    void calculateBoundingBox(double& minX, double& maxX, double& minY, double& maxY) {
        minX = minY = std::numeric_limits<double>::infinity();
        maxX = maxY = -std::numeric_limits<double>::infinity();
        
        for (const auto& site : sites) {
            minX = std::min(minX, site.x);
            maxX = std::max(maxX, site.x);
            minY = std::min(minY, site.y);
            maxY = std::max(maxY, site.y);
        }
        
        // Add some padding
        double padX = (maxX - minX) * 0.1;
        double padY = (maxY - minY) * 0.1;
        
        minX -= padX;
        maxX += padX;
        minY -= padY;
        maxY += padY;
    }
    
    // Complete any unfinished edges
    void completeEdges() {
        double minX, maxX, minY, maxY;
        calculateBoundingBox(minX, maxX, minY, maxY);
        
        for (auto& edge : edges) {
            // Skip already completed edges
            if (edge.start.x != 0 && edge.end.x != 0) {
                continue;
            }
            
            // Extend edge to bounding box
            // (This is a simplification; a proper implementation would
            // extend the edges correctly based on their direction)
            if (edge.start.x == 0) {
                edge.start = Point(minX, minY);
            }
            if (edge.end.x == 0) {
                edge.end = Point(maxX, maxY);
            }
        }
    }

public:
    FortuneAlgorithm(const std::vector<Point>& inputSites) : sites(inputSites), beachLineRoot(nullptr) {
        initialize();
    }
    
    ~FortuneAlgorithm() {
        cleanupBeachLine(beachLineRoot);
    }
    
    // Compute the Voronoi diagram and return the edges
    std::vector<Edge> compute() {
        // Process all events in order
        while (!siteEvents.empty() || !circleEvents.empty()) {
            if (circleEvents.empty() || 
                (!siteEvents.empty() && siteEvents.top().point.y > circleEvents.top().y)) {
                // Process site event
                SiteEvent event = siteEvents.top();
                siteEvents.pop();
                handleSiteEvent(event);
            } else {
                // Process circle event
                CircleEvent event = circleEvents.top();
                circleEvents.pop();
                handleCircleEvent(event);
            }
        }
        
        // Complete any unfinished edges
        completeEdges();
        
        return edges;
    }
};

// Function to visualize Voronoi diagram (text-based visualization)
void visualizeVoronoi(const std::vector<Point>& sites, const std::vector<Edge>& edges, 
                      int width, int height, double minX, double maxX, double minY, double maxY) {
    std::vector<std::vector<char>> grid(height, std::vector<char>(width, '.'));
    
    // Map real coordinates to grid coordinates
    auto mapX = [&](double x) -> int {
        return static_cast<int>((x - minX) / (maxX - minX) * (width - 1));
    };
    
    auto mapY = [&](double y) -> int {
        return static_cast<int>((y - minY) / (maxY - minY) * (height - 1));
    };
    
    // Draw the edges
    for (const auto& edge : edges) {
        int x1 = mapX(edge.start.x);
        int y1 = mapY(edge.start.y);
        int x2 = mapX(edge.end.x);
        int y2 = mapY(edge.end.y);
        
        // Bresenham's line algorithm to draw the edge
        int dx = std::abs(x2 - x1);
        int dy = std::abs(y2 - y1);
        int sx = (x1 < x2) ? 1 : -1;
        int sy = (y1 < y2) ? 1 : -1;
        int err = dx - dy;
        
        while (true) {
            if (x1 >= 0 && x1 < width && y1 >= 0 && y1 < height) {
                grid[y1][x1] = '*';
            }
            
            if (x1 == x2 && y1 == y2) break;
            
            int e2 = 2 * err;
            if (e2 > -dy) { err -= dy; x1 += sx; }
            if (e2 < dx) { err += dx; y1 += sy; }
        }
    }
    
    // Mark the sites
    for (const auto& site : sites) {
        int x = mapX(site.x);
        int y = mapY(site.y);
        
        if (x >= 0 && x < width && y >= 0 && y < height) {
            grid[y][x] = 'O';
        }
    }
    
    // Print the visualization
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << std::endl;
    }
}

// Example usage
int main() {
    // Example set of points
    std::vector<Point> sites = {
        {1.0, 1.0},
        {4.0, 1.0},
        {2.5, 3.0},
        {1.0, 4.0},
        {4.0, 4.0}
    };
    
    std::cout << "Computing Voronoi diagram for " << sites.size() << " sites..." << std::endl;
    
    // Compute Voronoi diagram
    FortuneAlgorithm fortune(sites);
    std::vector<Edge> edges = fortune.compute();
    
    std::cout << "Voronoi diagram computed with " << edges.size() << " edges." << std::endl;
    
    // Print the edges
    std::cout << "\nVoronoi edges:" << std::endl;
    for (const auto& edge : edges) {
        std::cout << "Edge from (" << edge.start.x << ", " << edge.start.y << ") "
                  << "to (" << edge.end.x << ", " << edge.end.y << ")" << std::endl;
    }
    
    // Calculate bounding box for visualization
    double minX = std::numeric_limits<double>::infinity();
    double maxX = -std::numeric_limits<double>::infinity();
    double minY = std::numeric_limits<double>::infinity();
    double maxY = -std::numeric_limits<double>::infinity();
    
    for (const auto& site : sites) {
        minX = std::min(minX, site.x);
        maxX = std::max(maxX, site.x);
        minY = std::min(minY, site.y);
        maxY = std::max(maxY, site.y);
    }
    
    // Add some padding
    double padX = (maxX - minX) * 0.1;
    double padY = (maxY - minY) * 0.1;
    
    minX -= padX;
    maxX += padX;
    minY -= padY;
    maxY += padY;
    
    // Visualize the Voronoi diagram
    std::cout << "\nVisualization of Voronoi diagram:" << std::endl;
    visualizeVoronoi(sites, edges, 50, 20, minX, maxX, minY, maxY);
    
    return 0;
}