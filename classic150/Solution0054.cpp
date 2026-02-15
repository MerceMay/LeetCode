#include <vector>
using namespace std;
// 给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。
class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        int top = 0, bottom = matrix.size() - 1;
        int left = 0, right = matrix[0].size() - 1;
        vector<int> result;
        while (top <= bottom && left <= right)
        {
            for (int i = left; i <= right; i++)
                result.push_back(matrix[top][i]);
            top++;
            for (int i = top; i <= bottom; i++)
                result.push_back(matrix[i][right]);
            right--;
            if (top <= bottom)
            {
                for (int i = right; i >= left; i--)
                    result.push_back(matrix[bottom][i]);
                bottom--;
            }
            if (left <= right)
            {
                for (int i = bottom; i >= top; i--)
                    result.push_back(matrix[i][left]);
                left++;
            }
        }
        return result;
    }
};