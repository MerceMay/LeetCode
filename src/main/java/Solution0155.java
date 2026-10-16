import java.lang.reflect.Array;
import java.util.*;

//设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
//
//实现 MinStack 类:
//
//MinStack() 初始化堆栈对象。
//void push(int value) 将元素 value 推入堆栈。
//void pop() 删除堆栈顶部的元素。
//int top() 获取堆栈顶部的元素。
//int getMin() 获取堆栈中的最小元素。

public class Solution0155 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String line1 = sc.nextLine();
        String line2 = sc.nextLine();

        String[] operations = Arrays.stream(
                        line1.substring(1, line1.length() - 1).split(","))
                .map(s -> s.trim().replace("\"", ""))
                .toArray(String[]::new);

        int[] argList = Arrays.stream(
                        line2.replaceAll("[\\[\\]]", "").split(","))
                .map(String::trim)
                .filter(s -> !s.isEmpty())
                .mapToInt(Integer::parseInt)
                .toArray();

        MinStack minStack = null;
        int argIndex = 0;

        System.out.print("[");
        for (int i = 0; i < operations.length; i++) {
            if (i > 0) {
                System.out.print(", ");
            }

            switch (operations[i]) {
                case "MinStack":
                    minStack = new MinStack();
                    System.out.print("null");
                    break;

                case "push":
                    minStack.push(argList[argIndex++]);
                    System.out.print("null");
                    break;

                case "pop":
                    minStack.pop();
                    System.out.print("null");
                    break;

                case "top":
                    System.out.print(minStack.top());
                    break;

                case "getMin":
                    System.out.print(minStack.getMin());
                    break;
            }
        }
        System.out.print("]");
    }

    public static class MinStack {

        private Deque<Integer> stack;
        private Deque<Integer> minValStack;

        public MinStack() {
            stack = new LinkedList<>();
            minValStack = new LinkedList<>();
            minValStack.push(Integer.MAX_VALUE);
        }

        public void push(int value) {
            stack.push(value);
            minValStack.push(Math.min(value, minValStack.peek()));
        }

        public void pop() {
            stack.pop();
            minValStack.pop();
        }

        public int top() {
            return stack.peek();
        }

        public int getMin() {
            return minValStack.peek();
        }
    }
}
