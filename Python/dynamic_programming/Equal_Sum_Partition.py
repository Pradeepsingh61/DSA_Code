def can_partition(nums):
    total_sum = sum(nums)

    if total_sum % 2 != 0:
        return False

    target = total_sum // 2
    n = len(nums)

    possible_sums = {0}

    for num in nums:
        new_sums = set()
        for s in possible_sums:
            new_sum = s + num
            if new_sum == target:
                return True
            if new_sum < target:
                new_sums.add(new_sum)
        possible_sums |= new_sums

    return target in possible_sums
