// you are given the value of n and u have to display the nth row
// n=3
// formula: nCr = n!/(r! * (n-r)!)

import java.util.*;

class PascalsTriangle {

    public static void main(String[] args) {
        int n = 5;
        List<Integer> list = new ArrayList<>();
        for (int c = 1; c <= n; c++) {
            list.add(nCr(n - 1, c - 1));
        }
        System.out.println(list.toString());

    }

    static int nCr(int r, int c) {
        int result = 1;
        for (int i = 0; i < c; i++) {
            result = result * (r - i);
            result = result / (i + 1);
        }
        return result;
    }
}
