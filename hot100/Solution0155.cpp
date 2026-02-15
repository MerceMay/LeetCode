#include <stack>
#include <climits>
using namespace std;
// 设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

// 实现 MinStack 类:

// MinStack() 初始化堆栈对象。
// void push(int val) 将元素val推入堆栈。
// void pop() 删除堆栈顶部的元素。
// int top() 获取堆栈顶部的元素。
// int getMin() 获取堆栈中的最小元素。

// 示例 1:

// 输入：
// ["MinStack","push","push","push","getMin","pop","top","getMin"]
// [[],[-2],[0],[-3],[],[],[],[]]

// 输出：
// [null,null,null,null,-3,null,0,-2]

// 解释：
// MinStack minStack = new MinStack();
// minStack.push(-2);
// minStack.push(0);
// minStack.push(-3);
// minStack.getMin();   --> 返回 -3.
// minStack.pop();
// minStack.top();      --> 返回 0.
// minStack.getMin();   --> 返回 -2.

// 提示：

// -231 <= val <= 231 - 1
// pop、top 和 getMin 操作总是在 非空栈 上调用
// push, pop, top, and getMin最多被调用 3 * 104 次
// push, pop, top使用常规栈实现思路
// getMin使用一个min_stack来记录常规栈中的最小值
class MinStack
{
private:
    stack<int> data_stack;
    stack<int> min_stack;

public:
    MinStack()
    {
        min_stack.push(INT_MAX);
    }

    void push(int val)
    {
        data_stack.push(val);
        min_stack.push(min(min_stack.top(), val));
    }

    void pop()
    {
        data_stack.pop();
        min_stack.pop();
    }

    int top()
    {
        return data_stack.top();
    }

    int getMin()
    {
        return min_stack.top();
    }
};