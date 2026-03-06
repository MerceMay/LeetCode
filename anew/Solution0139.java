package anew;

import java.util.List;

// 给你一个字符串 s 和一个字符串列表 wordDict 作为字典。如果可以利用字典中出现的一个或多个单词拼接出 s 则返回 true。

// 注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。

public class Solution0139 {
    public boolean wordBreak(String s, List<String> wordDict) {
        int n = s.length();
        boolean[] dp = new boolean[n + 1];
        dp[0] = true;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && wordDict.contains(s.substring(j, i))) {
                    dp[i] = true;
                }
            }
        }
        return dp[n];
    }

    public boolean wordBreak2(String s, List<String> wordDict) {
        int n = s.length();
        boolean[] dp = new boolean[n + 1];
        dp[0] = true;
        for (int i = 1; i <= n; i++) {
            for (String word : wordDict) {
                int len = word.length();
                if (i >= len && dp[i - len] && s.substring(i - len, i).equals(word)) {
                    dp[i] = true;
                }
            }
        }
        return dp[n];
    }

    public static void main(String[] args) {
        Solution0139 solution = new Solution0139();
        String s = "leetcode";
        List<String> wordDict = List.of("leet", "code");
        boolean result = solution.wordBreak(s, wordDict);
        System.out.println(result); // 输出: true (因为 "leetcode" 可以由 "leet" 和 "code" 拼接成)
        boolean result2 = solution.wordBreak2(s, wordDict);
        System.out.println(result2); // 输出: true (因为 "leetcode" 可以由 "leet" 和 "code" 拼接成)
    }
}
