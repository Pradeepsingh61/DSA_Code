/*
 * Interval Scheduling Algorithm (Greedy Approach)
 * 
 * Description:
 * The Interval Scheduling algorithm selects the maximum number of non-overlapping intervals
 * from a given set of intervals. It follows a greedy approach by:
 * 1. Sorting all intervals by their finishing times
 * 2. Selecting the interval with earliest finish time
 * 3. Discarding all intervals that overlap with the selected one
 * 4. Repeating steps 2-3 until no more intervals remain
 * 
 * Time Complexity: O(n log n) - dominated by the sorting operation
 * Space Complexity: O(n) - to store the intervals and results
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an interval with start and finish times
struct Interval {
    int start;
    int finish;
    int id;  // To identify the original position of the interval
    
    // Constructor
    Interval(int s, int f, int i) : start(s), finish(f), id(i) {}
};

// Function to print the intervals
void printIntervals(const vector<Interval>& intervals) {
    cout << "Intervals: " << endl;
    for (const auto& interval : intervals) {
        cout << "(" << interval.start << ", " << interval.finish << ") ID: " << interval.id << endl;
    }
}

// Function to find the maximum number of non-overlapping intervals
vector<Interval> intervalScheduling(vector<Interval>& intervals) {
    // If no intervals, return empty result
    if (intervals.empty()) {
        return {};
    }
    
    // Sort intervals by finish time
    sort(intervals.begin(), intervals.end(), 
         [](const Interval& a, const Interval& b) {
             return a.finish < b.finish;
         });
    
    // Vector to store selected intervals
    vector<Interval> result;
    
    // Select the first interval (with earliest finish time)
    result.push_back(intervals[0]);
    
    // Last selected interval's finish time
    int lastFinishTime = intervals[0].finish;
    
    // Iterate through remaining intervals
    for (size_t i = 1; i < intervals.size(); i++) {
        // If current interval's start time is >= last selected interval's finish time
        if (intervals[i].start >= lastFinishTime) {
            // Select this interval
            result.push_back(intervals[i]);
            // Update last finish time
            lastFinishTime = intervals[i].finish;
        }
    }
    
    return result;
}

// Main function with test cases
int main() {
    // Test Case 1: Basic example
    cout << "Test Case 1:" << endl;
    vector<Interval> intervals1 = {
        {1, 3, 1},  // (start, finish, id)
        {2, 5, 2},
        {3, 9, 3},
        {6, 8, 4},
        {5, 7, 5}
    };
    
    printIntervals(intervals1);
    vector<Interval> result1 = intervalScheduling(intervals1);
    
    cout << "\nSelected intervals:" << endl;
    printIntervals(result1);
    cout << "Maximum number of non-overlapping intervals: " << result1.size() << endl;
    
    // Test Case 2: All intervals overlap
    cout << "\nTest Case 2:" << endl;
    vector<Interval> intervals2 = {
        {1, 10, 1},
        {2, 6, 2},
        {3, 8, 3},
        {4, 9, 4}
    };
    
    printIntervals(intervals2);
    vector<Interval> result2 = intervalScheduling(intervals2);
    
    cout << "\nSelected intervals:" << endl;
    printIntervals(result2);
    cout << "Maximum number of non-overlapping intervals: " << result2.size() << endl;
    
    // Test Case 3: No overlapping intervals
    cout << "\nTest Case 3:" << endl;
    vector<Interval> intervals3 = {
        {1, 2, 1},
        {3, 4, 2},
        {5, 6, 3},
        {7, 8, 4}
    };
    
    printIntervals(intervals3);
    vector<Interval> result3 = intervalScheduling(intervals3);
    
    cout << "\nSelected intervals:" << endl;
    printIntervals(result3);
    cout << "Maximum number of non-overlapping intervals: " << result3.size() << endl;
    
    return 0;
}