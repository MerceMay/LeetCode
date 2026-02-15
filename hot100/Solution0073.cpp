#include <vector>
#include <algorithm>
using namespace std;
// 给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。请使用 原地 算法。

// 示例 1：

// 输入：matrix = [[1,1,1],[1,0,1],[1,1,1]]
// 输出：[[1,0,1],[0,0,0],[1,0,1]]
// 示例 2：

// 输入：matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
// 输出：[[0,0,0,0],[0,4,5,0],[0,3,1,0]]

// 提示：

// m == matrix.length
// n == matrix[0].length
// 1 <= m, n <= 200
// -231 <= matrix[i][j] <= 231 - 1

// 进阶：

// 一个直观的解决方案是使用  O(mn) 的额外空间，但这并不是一个好的解决方案。
// 一个简单的改进方案是使用 O(m + n) 的额外空间，但这仍然不是最好的解决方案。
// 你能想出一个仅使用常量空间的解决方案吗？

// 方法一：使用两个标记变量，标记第一行或第一列有没有0。然后遍历内部的元素，
// 如果一个元素是0，就将它所在的行和列标记为0。
// 当然，如果使用matrix[0][0]代替一个变量，则少一个标记变量，更方便
class Solution
{
public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        int row_length = matrix.size();
        int col_length = matrix[0].size();
        bool first_row_has_zero = false;
        bool first_col_has_zero = false;
        for (int i = 0; i < row_length; i++)
        {
            if (matrix[i][0] == 0)
            {
                first_col_has_zero = true;
                break;
            }
        }
        for (int j = 0; j < col_length; j++)
        {
            if (matrix[0][j] == 0)
            {
                first_row_has_zero = true;
                break;
            }
        }
        for (int i = 1; i < row_length; i++)
        {
            for (int j = 1; j < col_length; j++)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[i][0] = 0; // 标记第i行
                    matrix[0][j] = 0; // 标记第j列
                }
            }
        }
        for (int i = 1; i < row_length; i++)
        {
            for (int j = 1; j < col_length; j++)
            {
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                {
                    matrix[i][j] = 0;
                }
            }
        }
        if (first_col_has_zero)
        {
            for (int i = 0; i < row_length; i++)
            {
                matrix[i][0] = 0;
            }
        }
        if (first_row_has_zero)
        {
            for (int j = 0; j < col_length; j++)
            {
                matrix[0][j] = 0;
            }
        }
    }
};

// 当然，如果不适用原地标记，使用额外空间，则使用两个数组row(row_length)和col(col_length)，标记true即可
class Solution2
{
public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> row(m), col(n);
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (!matrix[i][j])
                {
                    row[i] = col[j] = true;
                }
            }
        }
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (row[i] || col[j])
                {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};