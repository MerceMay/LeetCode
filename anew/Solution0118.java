package anew;

import java.util.ArrayList;
import java.util.List;

// 给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。

// 在「杨辉三角」中，每个数是它左上方和右上方的数的和。

public class Solution0118 {
    public List<List<Integer>> generate(int numRows) {
        List<List<Integer>> result = new ArrayList<>();
        if (numRows <= 0) {
            return result;
        }
        result.add(List.of(1));
        for (int i = 1; i < numRows; i++) {
            List<Integer> list = new ArrayList<>();
            List<Integer> preList = result.get(i - 1);
            list.add(1);
            for (int j = 1; j < i; j++) {
                list.add(preList.get(j - 1) + preList.get(j));
            }
            list.add(1);
            result.add(list);
        }
        return result;
    }

    public static void main(String[] args) {
        Solution0118 solution = new Solution0118();
        System.out.println(solution.generate(5));
    }
}
