#include <vector>
using namespace std;
// 给你一个满足下述两条属性的 m x n 整数矩阵：

// 每行中的整数从左到右按非严格递增顺序排列。
// 每行的第一个整数大于前一行的最后一个整数。
// 给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。
class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        int rows = matrix.size();
        if (rows == 0)
            return false;
        int cols = matrix[0].size();
        int left = 0, right = rows * cols - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            int mid_value = matrix[mid / cols][mid % cols];
            if (mid_value == target)
                return true;
            else if (mid_value < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return false;
    }
};

// 两次二分查找
class Solution2
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        int rows = matrix.size();
        if (rows == 0)
            return false;
        int cols = matrix[0].size();
        int top = 0, bottom = rows - 1;
        while (top <= bottom)
        {
            int mid_row = top + (bottom - top) / 2;
            if (matrix[mid_row][0] == target)
                return true;
            else if (matrix[mid_row][0] < target)
                top = mid_row + 1;
            else
                bottom = mid_row - 1;
        }
        if (bottom < 0) // 说明matrix[0][0]就大于target，
            return false;
        int row = bottom;
        int left = 0, right = cols - 1;
        while (left <= right)
        {
            int mid_col = left + (right - left) / 2;
            if (matrix[row][mid_col] == target)
                return true;
            else if (matrix[row][mid_col] < target)
                left = mid_col + 1;
            else
                right = mid_col - 1;
        }
        return false;
    }
};

// 递归实现
class Solution3
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        return findMid(matrix, 0, (matrix.size() * matrix[0].size()) - 1, target);
    }
private:
    bool findMid(vector<vector<int>> &matrix, int left, int right, int target)
    {
        if (left > right) // left > right 时，这表示我们的搜索区间已经为空了
            return false;
        int mid = left + (right - left) / 2;
        int midValue = matrix[mid / matrix[0].size()][mid % matrix[0].size()];
        if (midValue == target)
            return true;
        else if (midValue < target)
            return findMid(matrix, mid + 1, right, target);
        else
            return findMid(matrix, left, mid - 1, target);
    }
};