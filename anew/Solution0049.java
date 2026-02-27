package anew;

import java.util.List;
import java.util.Map;
import java.util.HashMap;
import java.util.ArrayList;
import java.util.Arrays;
// 给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。

public class Solution0049 {
    public List<List<String>> groupAnagrams(String[] strs) {
        Map<String, List<String>> map = new HashMap<>();
        for (String str : strs) {
            char[] array = str.toCharArray();
            Arrays.sort(array);
            String key = str.toString();
            List<String> value = map.getOrDefault(key, new ArrayList<String>());
            value.add(str);
            map.put(key, value);
        }
        return new ArrayList<List<String>>(map.values());
    }

    public List<List<String>> groupAnagrams2(String[] strs) {
        Map<String, List<String>> map = new HashMap<>();
        for (String str : strs) {
            int[] count = new int[26];
            int length = str.length();
            for (int i = 0; i < length; i++) {
                count[str.charAt(i) - 'a']++;
            }

            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < 26; i++) {
                if (count[i] != 0) {
                    sb.append((char) ('a' + i));
                    sb.append(count[i]);
                }
            }
            String key = sb.toString();
            List<String> value = map.getOrDefault(key, new ArrayList<String>());
            value.add(str);
            map.put(key, value);
        }
        return new ArrayList<List<String>>(map.values());
    }
}
