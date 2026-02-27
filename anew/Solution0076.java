package anew;

import java.util.Map;
import java.util.HashMap;
// 给定两个字符串 s 和 t，长度分别是 m 和 n，返回 s 中的 最短窗口 子串，使得该子串包含 t 中的每一个字符（包括重复字符）。如果没有这样的子串，返回空字符串 ""。

// 测试用例保证答案唯一。
public class Solution0076 {
    public String minWindow(String s, String t) {
        Map<Character, Integer> need = new HashMap<>();
        Map<Character, Integer> window = new HashMap<>();
        for (char c : t.toCharArray()) {
            need.put(c, need.getOrDefault(c, 0) + 1);
        }
        int minLen = Integer.MAX_VALUE;
        int start = 0;
        int left = 0, right = 0;
        int valid = 0;
        while (right < s.length()) {
            char rightC = s.charAt(right++);
            if (need.containsKey(rightC)) {
                window.put(rightC, window.getOrDefault(rightC, 0) + 1);
                if (window.get(rightC).equals(need.get(rightC))) {
                    valid++;
                }
            }
            while (valid == need.size()) {
                if (right - left < minLen) {
                    start = left;
                    minLen = right - left;
                }
                char leftC = s.charAt(left++);
                if (need.containsKey(leftC)) {
                    if (window.get(leftC).equals(need.get(leftC))) {
                        valid--;
                    }
                    window.put(leftC, window.get(leftC) - 1);
                }
            }
        }
        return minLen == Integer.MAX_VALUE ? "" : s.substring(start, start + minLen);
    }

    public String minWindow2(String s, String t) {
        int[] count = new int[128];
        for (char c : t.toCharArray()) {
            count[c]++;
        }
        int start = 0, minLen = Integer.MAX_VALUE;
        int left = 0, right = 0;
        int valid = t.length();
        while (right < s.length()) {
            char rightC = s.charAt(right++);
            if (count[rightC] > 0) {
                valid--;
            }
            count[rightC]--;
            while (valid == 0) {
                if (right - left < minLen) {
                    start = left;
                    minLen = right - left;
                }
                char leftC = s.charAt(left++);
                count[leftC]++;
                if (count[leftC] > 0) {
                    valid++;
                }
            }
        }
        return minLen == Integer.MAX_VALUE ? "" : s.substring(start, start + minLen);
    }

    public static void main(String[] args) {
        Solution0076 solution0076 = new Solution0076();
        String s = "ADOBECODEBANC";
        String t = "ABC";
        System.out.println(solution0076.minWindow(s, t));
        System.out.println(solution0076.minWindow2(s, t));
    }
}
