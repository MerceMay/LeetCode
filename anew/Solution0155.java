package anew;

import java.util.Stack;

// 设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

// 实现 MinStack 类:

// MinStack() 初始化堆栈对象。
// void push(int val) 将元素val推入堆栈。
// void pop() 删除堆栈顶部的元素。
// int top() 获取堆栈顶部的元素。
// int getMin() 获取堆栈中的最小元素。

public class Solution0155 {
    private static class MinStack {
        private Stack<int[]> stack;

        public MinStack() {
            stack = new Stack<>();
            stack.push(new int[] { 0, Integer.MAX_VALUE });
        }

        public void push(int val) {
            stack.push(new int[] { val, Math.min(stack.peek()[1], val) });
        }

        public void pop() {
            stack.pop();
        }

        public int top() {
            return stack.peek()[0];
        }

        public int getMin() {
            return stack.peek()[1];
        }
    }

    public static void main(String[] args) {
        MinStack minStack = new MinStack();
        minStack.push(-2);
        minStack.push(0);
        minStack.push(-3);
        System.out.println(minStack.getMin()); // 返回 -3.
        minStack.pop();
        System.out.println(minStack.top()); // 返回 0.
        System.out.println(minStack.getMin()); // 返回 -2.
    }
}
