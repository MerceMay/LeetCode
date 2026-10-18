import java.util.*;

//给你一个字符串 s 。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。例如，字符串 "ababcc" 能够被分为 ["abab", "cc"]，但类似 ["aba", "bcc"] 或 ["ab", "ab", "cc"] 的划分是非法的。
//
//注意，划分结果需要满足：将所有划分结果按顺序连接，得到的字符串仍然是 s 。
//
//返回一个表示每个字符串片段的长度的列表。

public class Solution0763 {
    public List<Integer> partitionLabels(String s) {
        int[] last = new int[26];
        for (int i = 0; i < s.length(); i++) {
            last[s.charAt(i) - 'a'] = i;
        }
        List<Integer> result = new ArrayList<>();
        int farthest = 0;
        int lastI = 0;
        for (int i = 0; i < s.length(); i++) {
            farthest = Math.max(farthest, last[s.charAt(i) - 'a']);
            if (i == farthest) {
                result.add(i - lastI + 1);
                lastI = i + 1;
            }
        }
        return result;
    }
}
