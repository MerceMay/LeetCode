import java.util.*;

//给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。
//
//在「杨辉三角」中，每个数是它左上方和右上方的数的和。

public class Solution0118 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.out.println(generate(n));
        System.out.println(generate2(n));
    }

    static public List<List<Integer>> generate(int numRows) {
        List<List<Integer>> cache = new ArrayList<>();
        cache.add(new ArrayList<>() {{
            add(1);
        }});
        for (int i = 2; i <= numRows; i++) {
            List<Integer> list = new ArrayList<>();
            List<Integer> preList = cache.get(i - 2);
            list.add(1);
            for (int j = 1; j < i - 1; j++) {
                list.add(preList.get(j - 1) + preList.get(j));
            }
            list.add(1);
            cache.add(list);
        }
        return cache;
    }

    static public List<List<Integer>> generate2(int numRows) {
        List<List<Integer>> result = new ArrayList<>();
        for (int i = 0; i < numRows; i++) {
            List<Integer> row = new ArrayList<>();
            for (int j = 0; j <= i; j++) {
                if (j == 0 || j == i) {
                    row.add(1);
                } else {
                    row.add(result.get(i - 1).get(j - 1) + result.get(i - 1).get(j));
                }
            }
            result.add(row);
        }
        return result;
    }
}
