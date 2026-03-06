package anew;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

// 给你一个字符串 s 。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。例如，字符串 "ababcc" 能够被分为 ["abab", "cc"]，但类似 ["aba", "bcc"] 或 ["ab", "ab", "cc"] 的划分是非法的。

// 注意，划分结果需要满足：将所有划分结果按顺序连接，得到的字符串仍然是 s 。

// 返回一个表示每个字符串片段的长度的列表。

public class Solution0763 {
    public List<Integer> partitionLabels(String s) {
        int n = s.length();
        int[] first = new int[26];
        int[] last = new int[26];
        Arrays.fill(first, -1);
        for (int i = 0; i < n; i++) {
            int index = s.charAt(i) - 'a';
            if (first[index] == -1) {
                first[index] = i;
            }
            last[index] = i;
        }

        int[] dp = new int[n + 1];
        Arrays.fill(dp, -1);
        dp[0] = 0;

        int[] parent = new int[n + 1];

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] != -1 && valid(s, j, i - 1, first, last)) {
                    if (dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        parent[i] = j;
                    }
                }
            }
        }

        List<Integer> result = new LinkedList<>();
        int current = n;
        while (current > 0) {
            int prev = parent[current];
            result.add(0, current - prev);
            current = prev;
        }
        return result;
    }

    private boolean valid(String s, int start, int end, int[] first, int[] last) {
        for (int i = start; i <= end; i++) {
            int index = s.charAt(i) - 'a';
            if (first[index] < start || last[index] > end) {
                return false;
            }
        }
        return true;
    }

    // dp[i]是非递减的，
    // 因此，对于第i个字符，不断更新其maxReach，直到i==maxReach
    public List<Integer> partitionLabels2(String s) {
        int n = s.length();
        char[] chars = s.toCharArray();
        int[] last = new int[26];
        for (int i = 0; i < n; i++) {
            last[chars[i] - 'a'] = i;
        }

        List<Integer> result = new LinkedList<>();
        int start = 0;
        int maxReach = 0;
        for (int i = 0; i < n; i++) {
            maxReach = Math.max(maxReach, last[chars[i] - 'a']);
            if (i == maxReach) {
                result.add(maxReach - start + 1);
                start = maxReach + 1;
            }
        }
        return result;
    }

    public static void main(String[] args) {
        Solution0763 solution = new Solution0763();
        System.out.println(solution.partitionLabels("ababcbacadefegdehijhklij"));
        System.out.println(solution.partitionLabels2("ababcbacadefegdehijhklij"));
    }
}
