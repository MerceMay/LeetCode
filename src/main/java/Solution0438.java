import java.util.*;

//给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

public class Solution0438 {
    public List<Integer> findAnagrams(String s, String p) {
        int sLen = s.length(), pLen = p.length();
        List<Integer> result = new ArrayList<>();
        if (sLen < pLen) {
            return result;
        }
        int[] count = new int[26];
        for (int i = 0; i < pLen; i++) {
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
            result.add(0);
        }
        for (int i = 0; i < sLen - pLen; i++) {
            if (count[s.charAt(i) - 'a'] == 1) {
                diff--;
            } else if (count[s.charAt(i) - 'a'] == 0) {
                diff++;
            }
            count[s.charAt(i) - 'a']--;

            if (count[s.charAt(i + pLen) - 'a'] == -1) {
                diff--;
            } else if (count[s.charAt(i + pLen) - 'a'] == 0) {
                diff++;
            }
            count[s.charAt(i + pLen) - 'a']++;
            if (diff == 0) {
                result.add(i + 1);
            }
        }
        return result;
    }
}
