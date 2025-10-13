/**
 * Hungarian Algorithm (Kuhn-Munkres Algorithm)
 * 
 * Purpose: 
 * Solves the assignment problem, which is about finding the optimal assignment of n workers to n jobs,
 * where each worker-job pair has an associated cost, and the goal is to minimize the total cost.
 * 
 * Time Complexity: O(n³)
 * Space Complexity: O(n²)
 * 
 * Author: Abhiram
 * Date: October 13, 2025
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

class HungarianAlgorithm {
private:
    std::vector<std::vector<int>> costMatrix; // Original cost matrix
    std::vector<std::vector<int>> workMatrix; // Working copy of cost matrix
    int size;                                 // Size of the problem (n)
    std::vector<int> labelByWorker;           // Labels for workers
    std::vector<int> labelByJob;              // Labels for jobs
    std::vector<int> minSlackWorkerByJob;     // For each job, the worker that has minimum slack
    std::vector<int> minSlackValueByJob;      // For each job, the minimum slack value
    std::vector<int> matchJobByWorker;        // Which job is assigned to which worker
    std::vector<int> matchWorkerByJob;        // Which worker is assigned to which job
    std::vector<bool> committedWorkers;       // Workers committed to the search tree

    // Initializes the data structures needed for the algorithm
    void initialize() {
        // Initialize all jobs to unmatched status
        matchJobByWorker = std::vector<int>(size, -1);
        matchWorkerByJob = std::vector<int>(size, -1);
        committedWorkers = std::vector<bool>(size, false);
        
        // Initialize labels: worker labels to maximum cost in their row
        // job labels to 0
        labelByWorker = std::vector<int>(size, 0);
        labelByJob = std::vector<int>(size, 0);
        
        for (int w = 0; w < size; w++) {
            for (int j = 0; j < size; j++) {
                if (costMatrix[w][j] > labelByWorker[w]) {
                    labelByWorker[w] = costMatrix[w][j];
                }
            }
        }
    }

    // Executes an augmenting path algorithm to find an augmenting path
    bool executePhase() {
        // Reset committed workers
        std::fill(committedWorkers.begin(), committedWorkers.end(), false);
        
        // Reset jobs
        std::vector<bool> committedJobs(size, false);
        
        // Match all jobs to workers with zero slack
        for (int j = 0; j < size; j++) {
            matchWorkerByJob[j] = -1;
        }
        
        // Initialize min slack arrays
        minSlackWorkerByJob = std::vector<int>(size, -1);
        minSlackValueByJob = std::vector<int>(size);
        
        // Choose the first unmatched worker
        for (int w = 0; w < size; w++) {
            if (matchJobByWorker[w] == -1) {
                // Start the algorithm with this worker
                return findAugmentingPath(w);
            }
        }
        
        return false;
    }

    // Finds an augmenting path starting from a specific worker
    bool findAugmentingPath(int initialWorker) {
        committedWorkers[initialWorker] = true;
        
        // Initialize min slack for each job
        for (int j = 0; j < size; j++) {
            minSlackValueByJob[j] = labelByWorker[initialWorker] + labelByJob[j] - costMatrix[initialWorker][j];
            minSlackWorkerByJob[j] = initialWorker;
        }
        
        std::vector<bool> parentWorkerByCommittedJob(size, false);
        std::vector<int> parentWorkerByJob(size, -1);
        
        int worker = initialWorker;
        int job = -1;
        
        while (true) {
            // Find a job with minimum slack
            int minSlackJob = -1;
            int minSlackValue = std::numeric_limits<int>::max();
            
            for (int j = 0; j < size; j++) {
                if (parentWorkerByCommittedJob[j]) continue;
                
                if (minSlackValueByJob[j] < minSlackValue) {
                    minSlackValue = minSlackValueByJob[j];
                    minSlackJob = j;
                }
            }
            
            // Update labels for all committed workers and jobs
            if (minSlackValue > 0) {
                for (int w = 0; w < size; w++) {
                    if (committedWorkers[w]) labelByWorker[w] -= minSlackValue;
                }
                
                for (int j = 0; j < size; j++) {
                    if (parentWorkerByCommittedJob[j]) {
                        labelByJob[j] += minSlackValue;
                    } else {
                        minSlackValueByJob[j] -= minSlackValue;
                    }
                }
            }
            
            // Assign job to a worker
            parentWorkerByJob[minSlackJob] = minSlackWorkerByJob[minSlackJob];
            job = minSlackJob;
            
            // Check if we found a job that's unassigned
            if (matchWorkerByJob[job] == -1) {
                break;
            }
            
            // Add the worker to the committed set
            worker = matchWorkerByJob[job];
            committedWorkers[worker] = true;
            parentWorkerByCommittedJob[job] = true;
            
            // Update the min slack for all jobs
            for (int j = 0; j < size; j++) {
                if (parentWorkerByCommittedJob[j]) continue;
                
                int slack = labelByWorker[worker] + labelByJob[j] - costMatrix[worker][j];
                
                if (slack < minSlackValueByJob[j]) {
                    minSlackValueByJob[j] = slack;
                    minSlackWorkerByJob[j] = worker;
                }
            }
        }
        
        // Update the matching by following the augmenting path
        while (job != -1) {
            int nextWorker = parentWorkerByJob[job];
            int nextJob = matchJobByWorker[nextWorker];
            matchJobByWorker[nextWorker] = job;
            matchWorkerByJob[job] = nextWorker;
            job = nextJob;
        }
        
        return true;
    }

public:
    /**
     * Constructor that takes a cost matrix where costMatrix[i][j] represents 
     * the cost of assigning worker i to job j.
     */
    HungarianAlgorithm(const std::vector<std::vector<int>>& inputMatrix) {
        costMatrix = inputMatrix;
        size = costMatrix.size();
        
        // Make a working copy of the cost matrix
        workMatrix = costMatrix;
        
        // Initialize data structures
        initialize();
    }

    /**
     * Solves the assignment problem and returns the assignments and total cost.
     * Returns a pair where:
     * - First element is a vector of assignments (job assigned to each worker)
     * - Second element is the total cost of the assignment
     */
    std::pair<std::vector<int>, int> solve() {
        // Main algorithm loop - keep finding augmenting paths
        while (true) {
            if (!executePhase()) break;
        }
        
        // Calculate the final cost and create the assignment vector
        int totalCost = 0;
        for (int w = 0; w < size; w++) {
            int job = matchJobByWorker[w];
            totalCost += costMatrix[w][job];
        }
        
        return {matchJobByWorker, totalCost};
    }
};

// Utility function to print a matrix
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << "\t";
        }
        std::cout << std::endl;
    }
}

// Example usage
int main() {
    // Example cost matrix
    std::vector<std::vector<int>> costMatrix = {
        {250, 400, 350},
        {400, 600, 350},
        {200, 400, 250}
    };
    
    std::cout << "Cost Matrix:" << std::endl;
    printMatrix(costMatrix);
    std::cout << std::endl;
    
    // Create and solve the assignment problem
    HungarianAlgorithm ha(costMatrix);
    auto [assignments, totalCost] = ha.solve();
    
    std::cout << "Optimal Assignment:" << std::endl;
    for (int i = 0; i < assignments.size(); i++) {
        std::cout << "Worker " << i << " -> Job " << assignments[i] << " (Cost: " << costMatrix[i][assignments[i]] << ")" << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "Total Cost: " << totalCost << std::endl;
    
    return 0;
}