class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        n=len(nums)
        s1=set()
        if n<3:
            return 
        for i in range(0,n):
            low=i+1
            high=n-1
            while low<high:
                c=nums[i]+nums[low]+nums[high]
                if c==0:
                    s1.add((nums[i],nums[low],nums[high]))
                if c>=0:
                    high=high-1
                else:
                    low=low+1
        return list(s1)