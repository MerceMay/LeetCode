// n 位同学站成一排，音乐老师要请其中的 n−k 位同学出列，使得剩下的 k 位同学排成合唱队形。
// 合唱队形是指这样的一种队形：设 k 位同学从左到右依次编号为 1,2, … ,k，他们的身高分别为 t1,t2, … ,tk，则他们的身高满足 t1<⋯<ti>ti+1> … >tk(1≤i≤k)。
// 你的任务是，已知所有 n 位同学的身高，计算最少需要几位同学出列，可以使得剩下的同学排成合唱队形。
// 1，3，5，3，1 答案是0
// 186 186 150 200 160 130 197 220 答案是？186 186 200 160 130 3
#include <vector>
#include <iostream>
#include <stack>
using namespace std;

class Solution
{
private:
    stack<int> s1, s2;
    int count = 0;

public:
    int dequeue(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> LIS(n, 1), LDS(n, 1);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < i; j++)
                if (nums[j] < nums[i])
                    LIS[i] = max(LIS[i], LIS[j] + 1);

        for (int i = n - 1; i >= 0; i--)
            for (int j = n - 1; j > i; j--)
                if (nums[j] < nums[i])
                    LDS[i] = max(LDS[i], LDS[j] + 1);
        int maxLen = 0;
        for (int i = 0; i < n; i++)
            maxLen = max(maxLen, LIS[i] + LDS[i] - 1);
        return n - maxLen;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> testNums;
    testNums.push_back({1, 3, 5, 3, 1});
    testNums.push_back({1, 2, 3, 4, 1, 2, 3});
    testNums.push_back({10, 10, 10, 10, 10, 10});
    testNums.push_back({186, 186, 150, 200, 160, 130, 197, 220});
    for (auto &nums : testNums)
        cout << s.dequeue(nums) << endl;
    return 0;
}