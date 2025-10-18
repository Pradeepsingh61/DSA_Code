def checker(queens,i,j):
    for k in queens:
        if k[0] == i:
            return False
        if k[1] == j:
            return False
        if abs(k[0]-i) == abs(k[1]-j):
            return False
        if j-2>=0 and i+1<n:
            if k[0]==j-2 and k[1]==i+1:
                return False
        if j-2>=0 and i-1>=0:
            if k[0]==j-2 and k[1]==i-1:
                return False
        if j-1>=0 and i+1<n:
            if k[0]==j-2 and k[1]==i+1:
                return False
        if j-2>=0 and i+1<n:
            if k[0]==j-2 and k[1]==i+1:
                return False

    return True



board = []
for _ in range(8):
    row = list(input())
    board.append(row)
# print(board)

queens = []
n = 8
count = [0]
def main(i):
    if i==n:
        count[0]+=1
        return
    for j in range(8):
        if queens ==[] and board[i][j]!="*":
            queens.append([i,j])
            main(i+1)
            queens.pop()
        else:
            if checker(queens,i,j) and board[i][j]!="*":
                queens.append([i,j])
                main(i+1)
                queens.pop()
main(0)
print(count[0])

                



