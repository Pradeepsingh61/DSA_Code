class Solution(object):
    def maxArea(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        low=0

        high=len(height)-1

        m1=0

        m2=0

        while low<high:
            
            m2=min(height[low],height[high])

            m1=max(m1,m2*(high-low))

            if height[low]<height[high]:

                low=low+1

            else:

                high=high-1
                
        return m1
        