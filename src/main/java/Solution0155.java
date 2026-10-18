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
    class MinStack {
        private Deque<Integer> stack;
        private Deque<Integer> minValStack;

        public MinStack() {
            stack = new ArrayDeque<>();
            minValStack = new ArrayDeque<>();
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
