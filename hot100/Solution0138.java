package hot100;

import java.util.HashMap;
import java.util.Map;

// 给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。

// 构造这个链表的 深拷贝。 深拷贝应该正好由 n 个 全新 节点组成，其中每个新节点的值都设为其对应的原节点的值。新节点的 next 指针和 random 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。复制链表中的指针都不应指向原链表中的节点 。

// 例如，如果原链表中有 X 和 Y 两个节点，其中 X.random --> Y 。那么在复制链表中对应的两个节点 x 和 y ，同样有 x.random --> y 。

// 返回复制链表的头节点。

// 用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：

// val：一个表示 Node.val 的整数。
// random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。
// 你的代码 只 接受原链表的头节点 head 作为传入参数。
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
        if (head == null) {
            return null;
        }
        Map<Node, Node> map = new HashMap<>();
        Node dummy = new Node(0);
        Node current = dummy;
        Node node = head;
        while (node != null) {
            Node newNode = new Node(node.val);
            current.next = newNode;
            map.put(node, newNode);
            node = node.next;
            current = current.next;
        }

        node = head;
        current = dummy.next;
        while (node != null) {
            current.random = map.get(node.random);
            node = node.next;
            current = current.next;
        }
        return dummy.next;
    }

    private Map<Node, Node> map = new HashMap<>();

    public Node copyRandomList2(Node head) {
        if (head == null) {
            return null;
        }
        if (map.containsKey(head)) {
            return map.get(head);
        }
        Node newNode = new Node(head.val);
        map.put(head, newNode);
        newNode.next = copyRandomList2(head.next);
        newNode.random = copyRandomList2(head.random);
        return newNode;
    }

    public Node copyRandomList3(Node head) {
        if (head == null) {
            return null;
        }
        Node current = head;
        while (current != null) {
            Node newNode = new Node(current.val);
            newNode.next = current.next;
            current.next = newNode;
            current = newNode.next;
        }

        current = head;
        while (current != null) {
            if (current.random != null) {
                current.next.random = current.random.next;
            }
            current = current.next.next;
        }

        current = head;
        Node newHead = head.next;
        while (current != null) {
            Node newNode = current.next;
            current.next = newNode.next;
            if (newNode.next != null) {
                newNode.next = newNode.next.next;
            }
            current = current.next;
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

        Node copiedHead = new Solution0138().copyRandomList(node1);
        Node current = copiedHead;
        while (current != null) {
            int randomVal = (current.random != null) ? current.random.val : -1;
            System.out.println("Node val: " + current.val + ", Random points to: " + randomVal);
            current = current.next;
        }
    }
}
