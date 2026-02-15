#include <vector>
using namespace std;
// 编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：

// 每行的元素从左到右升序排列。
// 每列的元素从上到下升序排列。

// 示例 1：

// 输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
// 输出：true
// 示例 2：

// 输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
// 输出：false

// 提示：

// m == matrix.length
// n == matrix[i].length
// 1 <= n, m <= 300
// -109 <= matrix[i][j] <= 109
// 每行的所有元素从左到右升序排列
// 每列的所有元素从上到下升序排列
// -109 <= target <= 109
// 方法一：暴力求解
class Solution1
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        for (const auto &row : matrix)
        {
            for (int element : row)
            {
                if (element == target)
                {
                    return true;
                }
            }
        }
        return false;
    }
};
// 方法二：二分查找
class Solution2
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        for (const auto &row : matrix)
        {
            int left = 0, right = row.size() - 1;
            while (left <= right)
            {
                int mid = left + (right - left) / 2;
                if (row[mid] == target)
                {
                    return true;
                }
                else if (row[mid] < target)
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
            }
        }
        return false;
    }
};

// 方法三：从左下角或者右上角开始查找
class Solution3
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        int row_length = matrix.size();
        int col_length = matrix[0].size();
        int i = row_length - 1;
        int j = 0;
        while (i >= 0 && j < col_length)
        {
            if (matrix[i][j] == target)
            {
                return true;
            }
            else if (matrix[i][j] < target)
            {
                j++;
            }
            else
            {
                i--;
            }
        }
        return false;
    }
};