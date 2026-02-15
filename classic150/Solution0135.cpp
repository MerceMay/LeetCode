#include <vector>
using namespace std;
// n 个孩子站成一排。给你一个整数数组 ratings 表示每个孩子的评分。

// 你需要按照以下要求，给这些孩子分发糖果：

// 每个孩子至少分配到 1 个糖果。
// 相邻两个孩子中，评分更高的那个会获得更多的糖果。
// 请你给每个孩子分发糖果，计算并返回需要准备的 最少糖果数目 。

// 示例 1：

// 输入：ratings = [1,0,2]
// 输出：5
// 解释：你可以分别给第一个、第二个、第三个孩子分发 2、1、2 颗糖果。
// 示例 2：

// 输入：ratings = [1,2,2]
// 输出：4
// 解释：你可以分别给第一个、第二个、第三个孩子分发 1、2、1 颗糖果。
//      第三个孩子只得到 1 颗糖果，这满足题面中的两个条件。
class Solution
{
public:
    int candy(vector<int> &ratings)
    {
        vector<int> result(ratings.size(), 1);
        for (int i = 1; i < ratings.size(); i++)
        {
            if (ratings[i] > ratings[i - 1])
            {
                result[i] = result[i - 1] + 1;
            }
        }
        int total = 0;
        for (int i = ratings.size() - 2; i >= 0; i--)
        {
            if (ratings[i] > ratings[i + 1])
            {
                result[i] = max(result[i], result[i + 1] + 1);
            }
            total += result[i + 1];
        }
        return total + result[0];
    }
};

class Solution
{
public:
    int candy(vector<int> &ratings)
    {
        int result = 1;
        int increase = 1; // 上升坡长度
        int decrease = 0; // 下降坡长度
        int prev = 1;     // 前一个孩子分配到的糖果数
        for (int i = 1; i < ratings.size(); i++)
        {
            if (ratings[i] >= ratings[i - 1])
            {
                decrease = 0; // 下降坡重置为0
                prev = ratings[i] == ratings[i - 1] ? 1 : prev + 1; // 如果当前和前一个一样高，则糖果数为1，如果更大，则多一个
                result += prev; // 加入结构
                increase = prev; // 上升坡长度等于prev
            }
            else
            {
                decrease++; // 下降坡长度加1
                if (decrease == increase) // 如果下降坡长度等于上升坡长度，说明是峰值，既比左边高又比右边高，需要再加1，即加2
                {
                    decrease++;
                }
                result += decrease;
                prev = 1;
            }
        }
        return result;
    }
};