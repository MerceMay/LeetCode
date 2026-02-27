package anew;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

// 给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

public class Solution0438 {
    public List<Integer> findAnagrams(String s, String p) {
        List<Integer> res = new ArrayList<>();
        if (s.length() < p.length()) {
            return res;
        }
        int[] sCount = new int[128];
        int[] pCount = new int[128];
        for (int i = 0; i < p.length(); i++) {
            pCount[p.charAt(i)]++;
            sCount[s.charAt(i)]++;
        }
        if (Arrays.equals(sCount, pCount)) {
            res.add(0);
        }
        for (int i = p.length(); i < s.length(); i++) {
            sCount[s.charAt(i - p.length())]--;
            sCount[s.charAt(i)]++;
            if (Arrays.equals(sCount, pCount)) {
                res.add(i - p.length() + 1);
            }
        }
        return res;
    }

    public List<Integer> findAnagrams2(String s, String p) {
        List<Integer> res = new ArrayList<>();
        if (s.length() < p.length()) {
            return res;
        }
        int[] count = new int[26];
        for (int i = 0; i < p.length(); i++) {
            count[s.charAt(i) - 'a']++;
            count[p.charAt(i) - 'a']--;
        }
        int diff = 0;
        for (int i = 0; i < 26; i++) {
            if (count[i] != 0) {
                diff++;
            }
        }
        if (diff == 0) {
            res.add(0);
        }
        for (int i = p.length(); i < s.length(); i++) {
            char left = s.charAt(i - p.length());
            if (count[left - 'a'] == 0) {
                diff++;
            } else if (count[left - 'a'] == 1) {
                diff--;
            }
            count[left - 'a']--;

            char right = s.charAt(i);
            if (count[right - 'a'] == 0) {
                diff++;
            } else if (count[right - 'a'] == -1) {
                diff--;
            }
            count[right - 'a']++;

            if (diff == 0) {
                res.add(i - p.length() + 1);
            }
        }
        return res;
    }

    public static void main(String[] args) {
        Solution0438 solution0438 = new Solution0438();
        System.out.println(solution0438.findAnagrams("cbaebabacd", "abc"));
        System.out.println(solution0438.findAnagrams2("cbaebabacd", "abc"));
    }
}
