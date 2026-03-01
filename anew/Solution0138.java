package anew;

import java.util.Map;
import java.util.HashMap;

// 给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。

// 构造这个链表的 深拷贝。 深拷贝应该正好由 n 个 全新 节点组成，其中每个新节点的值都设为其对应的原节点的值。新节点的 next 指针和 random 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。复制链表中的指针都不应指向原链表中的节点 。

public class Solution0138 {
    private static class Node {
        int val;
        Node next;
        Node random;

        public Node(int val) {
            this.val = val;
            this.next = null;
            this.random = null;
        }
    }

    public Node copyRandomList(Node head) {
        Map<Node, Node> map = new HashMap<>();
        Node node = head;
        while (node != null) {
            map.put(node, new Node(node.val));
            node = node.next;
        }
        node = head;
        while (node != null) {
            Node newNode = map.get(node);
            newNode.next = map.getOrDefault(node.next, null);
            newNode.random = map.getOrDefault(node.random, null);
            node = node.next;
        }
        return map.get(head);
    }

    private Map<Node, Node> cache = new HashMap<>();

    public Node copyRandomList2(Node head) {
        if (head == null) {
            return null;
        }
        if (cache.containsKey(head)) {
            return cache.get(head);
        }
        Node newNode = new Node(head.val);
        cache.put(head, newNode);
        newNode.next = copyRandomList2(head.next);
        newNode.random = copyRandomList2(head.random);
        return newNode;
    }

    public Node copyRandomList3(Node head) {
        if (head == null) {
            return null;
        }

        for (Node curr = head; curr != null; curr = curr.next.next) {
            Node newNode = new Node(curr.val);
            newNode.next = curr.next;
            curr.next = newNode;
        }

        for (Node curr = head; curr != null; curr = curr.next.next) {
            Node newNode = curr.next;
            newNode.random = (curr.random != null) ? curr.random.next : null;
        }

        Node newHead = head.next;
        for (Node curr = head; curr != null; curr = curr.next) {
            Node newNode = curr.next;
            curr.next = newNode.next;
            newNode.next = (curr.next != null) ? curr.next.next : null;
        }
        return newHead;
    }

    public static void main(String[] args) {
        Node node1 = new Node(7);
        Node node2 = new Node(13);
        Node node3 = new Node(11);
        Node node4 = new Node(10);
        Node node5 = new Node(1);

        node1.next = node2;
        node2.next = node3;
        node3.next = node4;
        node4.next = node5;

        node2.random = node1;
        node3.random = node5;
        node4.random = node3;
        node5.random = node1;

        Node copiedHead = new Solution0138().copyRandomList3(node1);
        Node current = copiedHead;
        while (current != null) {
            int randomVal = (current.random != null) ? current.random.val : -1;
            System.out.println("Node val: " + current.val + ", Random points to: " + randomVal);
            current = current.next;
        }
    }
}
