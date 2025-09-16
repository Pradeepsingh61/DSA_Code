class Solution:
    def findKthBit(self, n: int, k: int) -> str:

        res = '0'
        
        for i in range(n -1):

            curr = '1'

            for j in range(len(res) - 1 , -1 , -1):

                if res[j] == '1':

                    curr += '0'

                else:

                    curr += '1'

            res += curr

        return res[k - 1]

