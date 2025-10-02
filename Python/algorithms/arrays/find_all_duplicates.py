"""
Author: Komal Srivastava
Time Complexity: O(n)
Space Complexity: O(1)
"""

def find_duplicates(nums):
    res = []
    for num in nums:
        index = abs(num) - 1
        if nums[index] < 0:
            res.append(abs(num))
        else:
            nums[index] *= -1
    return res

if __name__ == "__main__":
    sample = [4,3,2,7,8,2,3,1]
    print("Duplicates:", find_duplicates(sample))
