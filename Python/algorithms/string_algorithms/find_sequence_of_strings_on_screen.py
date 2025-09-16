class Solution:
    def stringSequence(self, target: str) -> List[str]:
        
        res = ""

        st  = []

        for i in target:

            res += 'a'

            st.append(res)

            while res[-1] != i:

                if res[-1] == 'z':

                    cur = 'a'

                    st.append(res[:-1] + cur)

                else:

                    cur = chr(ord(res[-1]) + 1)

                    st.append(res[:-1] + cur)

                res = res[:-1] + cur

        return st