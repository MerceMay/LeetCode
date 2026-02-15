package hot100;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

// 给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。
public class Solution0438 {
    public List<Integer> findAnagrams(String s, String p) {
        List<Integer> ans = new ArrayList<>();
        if (s.length() < p.length()) {
            return ans;
        }
        int[] sCount = new int[26];
        int[] pCount = new int[26];
        for (int i = 0; i < p.length(); i++) {
            sCount[s.charAt(i) - 'a']++;
            pCount[p.charAt(i) - 'a']++;
        }
        if (Arrays.equals(sCount, pCount))
            ans.add(0);
        for (int i = p.length(); i < s.length(); i++) {
            sCount[s.charAt(i - p.length()) - 'a']--;
            sCount[s.charAt(i) - 'a']++;
            if (Arrays.equals(sCount, pCount))
                ans.add(i - p.length() + 1);
        }
        return ans;
    }

    public List<Integer> findAnagrams2(String s, String p) {
        List<Integer> ans = new ArrayList<>();
        if (s.length() < p.length())
            return ans;
        int[] count = new int[26]; // 维护与p的差异，正值说明，窗口内该字符比p多，
        for (int i = 0; i < p.length(); i++) {
            count[s.charAt(i) - 'a']++;
            count[p.charAt(i) - 'a']--;
        }
        int diff = 0;
        for (int i = 0; i < 26; i++) {
            if (count[i] != 0)
                diff++;
        }
        if (diff == 0)
            ans.add(0);
        for (int i = p.length(); i < s.length(); i++) {
            int in = s.charAt(i) - 'a';
            if (count[in] == 0) {
                diff++;
            } else if (count[in] == -1) {
                diff--;
            }
            count[in]++;

            int out = s.charAt(i - p.length()) - 'a';
            if (count[out] == 0) {
                diff++;
            } else if (count[out] == 1) {
                diff--;
            }
            count[out]--;

            if (diff == 0)
                ans.add(i - p.length() + 1);
        }
        return ans;
    }

    public static void main(String[] args) {
        Solution0438 solution0438 = new Solution0438();
        System.out.println(solution0438.findAnagrams("cbaebabacd", "abc"));
        System.out.println(solution0438.findAnagrams2("cbaebabacd", "abc"));
    }
}
