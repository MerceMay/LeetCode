package hot100;

import java.util.Set;
import java.util.HashSet;
import java.util.List;
import java.util.ArrayList;

// 给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。
public class Solution0003 {
    public int lengthOfLongestSubstring(String s) {
        Set<Character> set = new HashSet<>();
        int maxLen = 0;
        int left = 0;
        for (int right = 0; right < s.length(); right++) {
            while (set.contains(s.charAt(right))) {
                set.remove(s.charAt(left));
                left++;
            }
            set.add(s.charAt(right));
            maxLen = Math.max(maxLen, right - left + 1);
        }
        return maxLen;
    }

    public int lengthOfLongestSubstring2(String s) {
        List<Integer> lastAppear = new ArrayList<>(128);
        for (int i = 0; i < 128; i++) {
            lastAppear.add(-1);
        }
        int maxLen = 0;
        int left = 0;
        for (int right = 0; right < s.length(); right++) {
            char c = s.charAt(right);
            left = Math.max(left, (int) lastAppear.get(c));
            maxLen = Math.max(maxLen, right - left + 1);
            lastAppear.set(c, right + 1);
        }
        return maxLen;
    }

    public static void main(String[] args) {
        Solution0003 solution0003 = new Solution0003();
        System.out.println(solution0003.lengthOfLongestSubstring("abcabcbb"));
        System.out.println(solution0003.lengthOfLongestSubstring2("abcabcbb"));
    }
}
