// https : // leetcode.com/problems/minimum-bit-flips-to-convert-number/description/

#include <bits/stdc++.h>

using namespace std;

/*
////////////////////////////////// BRUTE FORCE SOLUTION

int minBitFlips(int start, int goal)
    {
        int count = 0;
        for (int i = 0; i < 31; i++)
        {
            int a = (1 << i);
            bool test1 = (1 << i) & start;
            if (((1 << i) & start) != ((1 << i) & goal))
            {
                count++;
            }
        }
    return count;
}
TC:- O(1) for each time it is 31, dropping the constants!
SC:- O(1)
*/

int minBitFlips(int start, int goal)
{
    int count = 0, sum1 = 0, sum2 = 0, i = 0;
    while ((sum1 != start) || (sum2 != goal))
    {
        int a = (1 << i);
        bool test1 = (1 << i) & start;
        if ((1 << i) & start)
        {
            sum1 += a;
        }
        if ((1 << i) & goal)
        {
            sum2 += a;
        }
        if (((1 << i) & start) != ((1 << i) & goal))
        {
            count++;
        }
        cout<<"Sum1: "<<sum1<<"    Sum2:  "<<sum2<<endl;
        cout << "Response: " << test1 << "   Count: " << count << endl;

        i++;
    }

    return count;
}

int main()
{
    // return minBitFlips(10,7);
    return minBitFlips(3, 4);
}

// TC :- O(n) where is the number of bits used by the largest number between START and GOAL
// SC :- O(1) no extra space used as such!