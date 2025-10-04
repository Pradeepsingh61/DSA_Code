# You are climbing a staircase. It takes n steps to reach the top.
# Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
# Input
# First and only line of the input contains an integer value representing n.
# Note:
# As this is a functional problem, you just need to complete the function climbStairs with n as an integer parameter.


def climbStairs(n):
    if n==1:
        return  1

    if n==2:
        return 2

    first_step=1
    second_step=2
    for i in range(3,n+1):
            current_step = first_step + second_step
            first_step = second_step
            second_step = current_step
    return second_step



Input:
3
Output :
3
Explanation:
There are 3 ways to climb till the 3rd stair.
0 -> 1 -> 2 -> 3
0 -> 1 -> 3
0 -> 2 -> 3







