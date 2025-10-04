# Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.

# this is a functional problem, Your task is to complete the function permute which takes an array nums as it's input parameter and returns the 2D array which contains all the permutations of the given array.

# Custom Input
# The first line of the input contains a single integer N, denoting the size of an array.
# The second line of the input contains N space separated integers, denoting the elements of an array.

def permute(nums):
    if len(nums) == 0:
        return []
    if len(nums) == 1:
        return [[nums[0]]]

    smaller = permute(nums[1:])
    result = []

    for perm in smaller:
        for i in range(len(perm) + 1):
            new_perm = perm.copy()
            new_perm.insert(i, nums[0])
            result.append(new_perm)

    return result





# Sample Input
3
1 2 3
# Sample Output
1 2 3
1 3 2
2 1 3
2 3 1
3 2 1
3 1 2
# Explanation
[1, 2, 3]: The original order.
[1, 3, 2]: 3 is swapped with 2.
[2, 1, 3]: 1 is swapped with 2.
[2, 3, 1]: 1 is moved to the end.
[3, 2, 1]: The array is reversed.
[3, 1, 2]: 3 is moved to the start.



