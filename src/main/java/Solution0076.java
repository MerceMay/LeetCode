import java.util.*;

//给定两个字符串 s 和 t，长度分别是 m 和 n，返回 s 中的 最短窗口 子串，使得该子串包含 t 中的每一个字符（包括重复字符）。如果没有这样的子串，返回空字符串 ""。
//
//测试用例保证答案唯一。

public class Solution0076 {
    public String minWindow(String s, String t) {
        int sLen = s.length(), tLen = t.length();
        if (sLen < tLen) {
            return "";
        }
        int[] window = new int[128];
        for (char c : t.toCharArray()) {
            window[c]++;
        }
        int minLen = Integer.MAX_VALUE;
        int minStart = 0;
        int count = tLen;
        int left = 0, right = 0;
        while (right < sLen) {
            char rChar = s.charAt(right);
            if (window[rChar] > 0) {
                count--;
            }
            window[rChar]--;
            right++;
            while (count == 0) {
                int len = right - left;
                if (minLen > len) {
                    minLen = len;
                    minStart = left;
                }
                char lChar = s.charAt(left);
                window[lChar]++;
                if (window[lChar] > 0) {
                    count++;
                }
                left++;
            }
        }
        return minLen == Integer.MAX_VALUE ? "" : s.substring(minStart, minStart + minLen);
    }
}
