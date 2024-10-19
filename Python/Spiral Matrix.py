class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        res=[]

        if len(matrix)==0:

            return res

        row_start,col_start=0,0

        start,end=len(matrix)-1,len(matrix[0])-1

        while row_start<=start and col_start<=end:

            for i in range(col_start,end+1):

                res.append(matrix[row_start][i])

            row_start=row_start+1

            #print(res)
            for j in range(row_start,start+1):

                res.append(matrix[j][end])

            end=end-1

            #print(res)
            if row_start<=start:

                for i in range(end,col_start-1,-1):

                    res.append(matrix[start][i])

                start=start-1

            #print(res)

            if col_start<=end:

                for j in range(start,row_start-1,-1):

                    res.append(matrix[j][col_start])

                col_start=col_start+1

            #print(res)
            
        return res
            