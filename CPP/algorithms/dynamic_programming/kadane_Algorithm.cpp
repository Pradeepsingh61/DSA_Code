#include <vector>
#include <algorithm>
#include <climits>

int kadane(std::vector<int> &nums)
{
    if (nums.empty())
    {
        return 0;
    }

    int max_so_far = INT_MIN;
    int max_ending_here = 0;

    for (int num : nums)
    {
        max_ending_here = max_ending_here + num;

        if (max_so_far < max_ending_here)
        {
            max_so_far = max_ending_here;
        }

        if (max_ending_here < 0)
        {
            max_ending_here = 0;
        }
    }

    if (max_so_far == INT_MIN)
    {
        int max_val = nums[0];
        for (size_t i = 1; i < nums.size(); ++i)
        {
            if (nums[i] > max_val)
            {
                max_val = nums[i];
            }
        }
        return max_val;
    }

    return max_so_far;
}

// A slightly cleaner version that handles all-negative arrays without a separate check.
int kadane_optimized(std::vector<int> &nums)
{
    if (nums.empty())
    {
        return 0;
    }

    int max_so_far = nums[0];
    int current_max = nums[0];

    for (size_t i = 1; i < nums.size(); ++i)
    {
        current_max = std::max(nums[i], current_max + nums[i]);
        max_so_far = std::max(max_so_far, current_max);
    }

    return max_so_far;
}