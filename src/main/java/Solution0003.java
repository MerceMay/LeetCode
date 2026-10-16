import java.util.*;

//给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。

public class Solution0003 {
    public int lengthOfLongestSubstring(String s) {
        int n = s.length();
        if (n == 0) {
            return 0;
        }
        int[] lastOccur = new int[128];
        int maxLen = 0;
        int start = 0;
        for (int i = 0; i < n; i++) {
            char c = s.charAt(i);
            if (lastOccur[c] != 0) {
                start = Math.max(start, lastOccur[c]);
            }
            lastOccur[c] = i + 1;
            maxLen = Math.max(maxLen, i - start + 1);
        }
        return maxLen;
    }
}
