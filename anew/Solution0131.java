package anew;

import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;

// 给你一个字符串 s，请你将 s 分割成一些 子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。

public class Solution0131 {
    public List<List<String>> partition(String s) {
        List<List<String>> res = new ArrayList<>();
        List<String> path = new ArrayList<>();
        backtrack1(s, 0, res, path);
        return res;
    }

    private void backtrack1(String s, int index, List<List<String>> res, List<String> path) {
        if (index == s.length()) {
            res.add(new ArrayList<>(path));
            return;
        }
        for (int i = index; i < s.length(); i++) {
            if (isPalindrome1(s, index, i)) {
                path.add(s.substring(index, i + 1));
                backtrack1(s, i + 1, res, path);
                path.remove(path.size() - 1);
            }
        }
    }

    private boolean isPalindrome1(String s, int left, int right) {
        while (left < right) {
            if (s.charAt(left) != s.charAt(right))
                return false;
            left++;
            right--;
        }
        return true;
    }

    private boolean[][] cache2;

    public List<List<String>> partition2(String s) {
        List<List<String>> res = new ArrayList<>();
        cache2 = new boolean[s.length()][s.length()];
        for (int i = s.length() - 1; i >= 0; i--) {
            for (int j = i; j < s.length(); j++) {
                if (s.charAt(i) == s.charAt(j)) {
                    cache2[i][j] = (j - i < 2) || cache2[i + 1][j - 1];
                }

            }
        }
        backtrack2(s, 0, res, new ArrayList<>());
        return res;
    }

    private void backtrack2(String s, int index, List<List<String>> res, List<String> path) {
        if (index == s.length()) {
            res.add(new ArrayList<>(path));
            return;
        }
        for (int i = index; i < s.length(); i++) {
            if (cache2[index][i]) {
                path.add(s.substring(index, i + 1));
                backtrack2(s, i + 1, res, path);
                path.remove(path.size() - 1);
            }
        }
    }

    private int[][] cache3;

    public List<List<String>> partition3(String s) {
        List<List<String>> res = new ArrayList<>();
        cache3 = new int[s.length()][s.length()];
        backtrack3(s, 0, res, new ArrayList<>());
        return res;
    }

    private void backtrack3(String s, int index, List<List<String>> res, List<String> path) {
        if (index == s.length()) {
            res.add(new ArrayList<>(path));
            return;
        }
        for (int i = index; i < s.length(); i++) {
            if (isPalindrome3(s, index, i)) {
                path.add(s.substring(index, i + 1));
                backtrack3(s, i + 1, res, path);
                path.remove(path.size() - 1);
            }
        }
    }

    private boolean isPalindrome3(String s, int left, int right) {
        if (cache3[left][right] != 0) {
            return cache3[left][right] == 1;
        }
        if (left >= right) {
            cache3[left][right] = 1;
            return true;
        }
        if (s.charAt(left) == s.charAt(right) && isPalindrome3(s, left + 1, right - 1)) {
            cache3[left][right] = 1;
        } else {
            cache3[left][right] = -1;
        }
        return cache3[left][right] == 1;
    }

    public static void main(String[] args) {
        Solution0131 solution = new Solution0131();
        String s = "aab";
        List<List<String>> ans = solution.partition(s);
        System.out.println(ans);

        List<List<String>> ans2 = solution.partition2(s);
        System.out.println(ans2);

        List<List<String>> ans3 = solution.partition3(s);
        System.out.println(ans3);
    }
}
