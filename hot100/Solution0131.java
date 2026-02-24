package hot100;

import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;

// 给你一个字符串 s，请你将 s 分割成一些 子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。

public class Solution0131 {
    public List<List<String>> partition(String s) {
        List<List<String>> ans = new ArrayList<>();
        backtrack(ans, new ArrayList<>(), s, 0);
        return ans;
    }

    private void backtrack(List<List<String>> ans, List<String> path, String s, int index) {
        if (index == s.length()) {
            ans.add(new ArrayList<>(path));
            return;
        }
        for (int i = index; i < s.length(); i++) {
            if (isPalindrome(s, index, i)) {
                path.add(s.substring(index, i + 1));
                backtrack(ans, path, s, i + 1);
                path.remove(path.size() - 1);
            }
        }
    }

    private boolean isPalindrome(String s, int left, int right) {
        while (left < right) {
            if (s.charAt(left) != s.charAt(right)) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

    private boolean[][] cache2;

    public List<List<String>> partition2(String s) {
        List<List<String>> ans = new ArrayList<>();
        cache2 = new boolean[s.length()][s.length()];
        for (int i = 0; i < s.length(); i++) {
            Arrays.fill(cache2[i], true);
        }
        for (int i = s.length() - 1; i >= 0; i--) {
            for (int j = i + 1; j < s.length(); j++) {
                cache2[i][j] = s.charAt(i) == s.charAt(j) && cache2[i + 1][j - 1];
            }
        }
        backtrack2(ans, new ArrayList<>(), s, 0);
        return ans;
    }

    private void backtrack2(List<List<String>> ans, List<String> path, String s, int index) {
        if (index == s.length()) {
            ans.add(new ArrayList<>(path));
            return;
        }
        for (int i = index; i < s.length(); i++) {
            if (cache2[index][i]) {
                path.add(s.substring(index, i + 1));
                backtrack2(ans, path, s, i + 1);
                path.remove(path.size() - 1);
            }
        }
    }

    private int[][] cache3; // 0: unknown, 1: palindrome, -1: not palindrome

    public List<List<String>> partition3(String s) {
        cache3 = new int[s.length()][s.length()];
        List<List<String>> ans = new ArrayList<>();
        backtrack3(ans, new ArrayList<>(), s, 0);
        return ans;
    }

    private void backtrack3(List<List<String>> ans, List<String> path, String s, int index) {
        if (index == s.length()) {
            ans.add(new ArrayList<>(path));
            return;
        }
        for (int i = index; i < s.length(); i++) {
            if (isPalindrome3(s, index, i)) {
                path.add(s.substring(index, i + 1));
                backtrack3(ans, path, s, i + 1);
                path.remove(path.size() - 1);
            }
        }
    }

    private boolean isPalindrome3(String s, int left, int right) {
        if (cache3[left][right] == 1) {
            return true;
        }
        if (left >= right) {
            cache3[left][right] = 1;
            return true;
        }
        if (s.charAt(left) == s.charAt(right) && isPalindrome3(s, left + 1, right - 1)) {
            cache3[left][right] = 1;
            return true;
        }
        cache3[left][right] = -1;
        return false;
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
