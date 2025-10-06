/*
 * Problem Name:
 * Asteroid Collision
 *
 * Programming Language:
 * C++
 *
 * Category:
 * Stack / Simulation
 *
 * Difficulty Level:
 * Medium
 *
 * Problem Description:
 * You are given an array `asteroids` of integers representing asteroids in a row.
 * For each asteroid, the absolute value represents its size, and the sign represents
 * its direction (positive = right, negative = left). Each asteroid moves at the same speed.
 * 
 * If two asteroids meet, the smaller one will explode. If both are the same size, both explode.
 * Return the state of the asteroids after all collisions.
 *
 * Example:
 * Input: asteroids = [5, 10, -5]
 * Output: [5, 10]
 * Explanation: 10 and -5 collide and -5 explodes. 5 and 10 never collide.
 *
 * Time Complexity: O(N) — Each asteroid is pushed and popped at most once
 * Space Complexity: O(N) — Stack is used to track ongoing asteroids
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> st;
        int n = asteroids.size();
        
        for(int i = 0; i < n; i++){
            if(asteroids[i] > 0) {
                // Right-moving asteroid, push to stack
                st.push(asteroids[i]);
            } else {
                // Left-moving asteroid, check collisions
                while(!st.empty() && st.top() > 0 && st.top() < abs(asteroids[i])) {
                    st.pop(); // Smaller right-moving asteroid explodes
                }
                if(!st.empty() && st.top() == abs(asteroids[i])) {
                    st.pop(); // Both explode
                } else if(st.empty() || st.top() < 0) {
                    st.push(asteroids[i]); // No collision, push left-moving asteroid
                }
            }
        }

        // Build the result from the stack
        vector<int> ans(st.size());
        for(int i = st.size() - 1; i >= 0; i--) {
            ans[i] = st.top();
            st.pop();
        }

        return ans;
    }
};

// ---------------- Driver Code ----------------
int main() {
    Solution sol;
    vector<int> asteroids = {5, 10, -5};
    vector<int> result = sol.asteroidCollision(asteroids);

    cout << "Asteroids after collisions: ";
    for(int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
