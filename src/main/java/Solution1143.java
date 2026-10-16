import java.util.*;

//给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。
//
//一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
//
//例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
//两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。

public class Solution1143 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String text1 = sc.nextLine();
        String text2 = sc.nextLine();
        System.out.println(longestCommonSubsequence(text1, text2));
        System.out.println(longestCommonSubsequence2(text1, text2));
    }

    public static int longestCommonSubsequence(String text1, String text2) {
        int n1 = text1.length();
        int n2 = text2.length();
        int[][] dp = new int[n1 + 1][n2 + 1];
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                if (text1.charAt(i - 1) == text2.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[n1][n2];
    }

    public static int longestCommonSubsequence2(String text1, String text2) {
        int n1 = text1.length();
        int n2 = text2.length();

        int[] dp = new int[n2 + 1];
        for (int i = 1; i <= n1; i++) {
            int pre = 0;
            for (int j = 1; j <= n2; j++) {
                int temp = dp[j];
                if (text1.charAt(i - 1) == text2.charAt(j - 1)) {
                    dp[j] = pre + 1;
                } else {
                    dp[j] = Math.max(dp[j], dp[j - 1]);
                }
                pre = temp;
            }
        }
        return dp[n2];
    }
}
