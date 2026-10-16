import java.util.*;
//Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补全和拼写检查。
//
//请你实现 Trie 类：
//
//Trie() 初始化前缀树对象。
//void insert(String word) 向前缀树中插入字符串 word 。
//boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
//boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。


public class Solution0208 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String operationsLine = sc.nextLine();
        String valuesLine = sc.nextLine();

        String[] operations = operationsLine.substring(1, operationsLine.length() - 1).replace("\"", "").split(",\\s*");
        String[] values = valuesLine.substring(1, valuesLine.length() - 1).split("],\\s*\\[");

        Trie trie = null;
        List<Object> result = new ArrayList<>();
        for (int i = 0; i < operations.length; i++) {
            String operation = operations[i].trim();
            String value = values[i].replace("[", "").replace("]", "").replace("\"", "").trim();
            switch (operation) {
                case "Trie":
                    trie = new Trie();
                    result.add(null);
                    break;
                case "insert":
                    trie.insert(value);
                    result.add(null);
                    break;
                case "search":
                    result.add(trie.search(value));
                    break;
                case "startWith":
                    result.add(trie.startsWith(value));
                    break;
            }
        }
        System.out.println(result);
    }

    private static class TrieNode {
        int pass = 0;
        int end = 0;
        TrieNode[] nexts = new TrieNode[26];
    }

    public static class Trie {
        private TrieNode root;

        public Trie() {
            root = new TrieNode();
        }

        public void insert(String word) {
            if (word == null || word.isEmpty()) {
                return;
            }
            TrieNode cur = root;
            cur.pass++;
            for (char c : word.toCharArray()) {
                int index = c - 'a';
                if (cur.nexts[index] == null) {
                    cur.nexts[index] = new TrieNode();
                }
                cur = cur.nexts[index];
                cur.pass++;
            }
            cur.end++;
        }

        public boolean search(String word) {
            if (word == null || word.isEmpty()) {
                return false;
            }
            TrieNode cur = root;
            for (char c : word.toCharArray()) {
                int index = c - 'a';
                if (cur.nexts[index] == null) {
                    return false;
                }
                cur = cur.nexts[index];
            }
            return cur.end > 0;
        }

        public boolean startsWith(String prefix) {
            if (prefix == null || prefix.isEmpty()) {
                return root.pass > 0;
            }
            TrieNode cur = root;
            for (char c : prefix.toCharArray()) {
                int index = c - 'a';
                if (cur.nexts[index] == null) {
                    return false;
                }
                cur = cur.nexts[index];
            }
            return true;
        }

        public void delete(String word) {
            if (!search(word)) {
                return;
            }
            TrieNode cur = root;
            cur.pass--;
            for (char c : word.toCharArray()) {
                int index = c - 'a';
                if (--cur.nexts[index].pass == 0) {
                    cur.nexts[index] = null;
                    return;
                }
                cur = cur.nexts[index];
            }
            cur.end--;
        }
    }
}
