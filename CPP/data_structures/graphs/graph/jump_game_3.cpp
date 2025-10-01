#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool canReach(vector<int>& nums, int startIndex) {
        vector<int> visited(nums.size(), 0);
        return explore(nums, startIndex, visited);
    }

private:
    bool explore(vector<int>& nums, int currentIndex, vector<int>& visited) {
        if (currentIndex < 0 || currentIndex >= nums.size()) return false;
        if (visited[currentIndex]) return false;
        if (nums[currentIndex] == 0) return true;

        visited[currentIndex] = 1;

        return explore(nums, currentIndex + nums[currentIndex], visited) ||
               explore(nums, currentIndex - nums[currentIndex], visited);
    }
};

int main() {
    Solution solution;

    vector<int> nums = {4, 2, 3, 0, 3, 1, 2};
    int startIndex = 5;

    bool result = solution.canReach(nums, startIndex);
    cout << (result ? "Reachable" : "Not Reachable") << endl;

    return 0;
}
