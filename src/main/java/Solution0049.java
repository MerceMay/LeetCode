import java.util.*;

//给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。

public class Solution0049 {
    public List<List<String>> groupAnagrams(String[] strs) {
        Map<String, List<String>> map = new HashMap<>();
        for (String str : strs) {
            int[] counts = new int[26];
            for (char c : str.toCharArray()) {
                counts[c - 'a']++;
            }
            String key = Arrays.toString(counts);
            List<String> value = map.getOrDefault(key, new ArrayList<>());
            value.add(str);
            map.put(key, value);
        }
        return new ArrayList<>(map.values());
    }
}
