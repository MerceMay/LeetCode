import java.util.*;

//请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
//实现 LRUCache 类：
//LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
//int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
//void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
//函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。

public class Solution0146 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line1 = sc.nextLine();
        String line2 = sc.nextLine();
        String[] operations = Arrays.stream(line1.substring(1, line1.length() - 1).split(","))
                .map(s -> s.trim().replace("\"", ""))
                .toArray(String[]::new);
        int[][] argList = Arrays.stream(line2.substring(2, line2.length() - 2).split("],\\s*\\["))
                .map(s -> Arrays.stream(s.split(","))
                        .map(String::trim)
                        .mapToInt(Integer::parseInt)
                        .toArray())
                .toArray(int[][]::new);
        LRUCache cache = null;
        System.out.print("[");
        for (int i = 0; i < operations.length; i++) {
            if (i > 0) {
                System.out.print(", ");
            }
            switch (operations[i]) {
                case "LRUCache":
                    cache = new LRUCache(argList[i][0]);
                    System.out.print("null");
                    break;
                case "put":
                    cache.put(argList[i][0], argList[i][1]);
                    System.out.print("null");
                    break;
                case "get":
                    System.out.print(cache.get(argList[i][0]));
                    break;
            }
        }
        System.out.println("]");
    }

    public static class LRUCache {

        private static class Node {
            int key, value;
            Node prev, next;

            Node() {
            }

            Node(int k, int v) {
                key = k;
                value = v;
                prev = null;
                next = null;
            }
        }

        private Node head, tail;
        private int size, capacity;
        private Map<Integer, Node> map = new HashMap<>();

        public LRUCache(int capacity) {
            this.size = 0;
            this.capacity = capacity;
            head = new Node();
            tail = new Node();
            head.next = tail;
            tail.prev = head;
        }

        public int get(int key) {
            Node node = map.get(key);
            if (node == null) {
                return -1;
            } else {
                moveToHead(node);
                return node.value;
            }
        }

        public void put(int key, int value) {
            Node node = map.get(key);
            if (node == null) {
                Node newNode = new Node(key, value);
                map.put(key, newNode);
                addToHead(newNode);
                size++;
                if (size > capacity) {
                    Node tail = removeTail();
                    map.remove(tail.key);
                    size--;
                }
            } else {
                node.value = value;
                moveToHead(node);
            }
        }

        private void addToHead(Node node) {
            node.next = head.next;
            node.prev = head;
            head.next.prev = node;
            head.next = node;
        }

        private void moveToHead(Node node) {
            node.prev.next = node.next;
            node.next.prev = node.prev;
            addToHead(node);
        }

        private Node removeTail() {
            Node node = tail.prev;
            node.prev.next = tail;
            tail.prev = node.prev;
            return node;
        }
    }
}
