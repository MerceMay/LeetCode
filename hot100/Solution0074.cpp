#include <vector>
#include <algorithm>
using namespace std;
// 给你一个满足下述两条属性的 m x n 整数矩阵：

// 每行中的整数从左到右按非严格递增顺序排列。
// 每行的第一个整数大于前一行的最后一个整数。
// 给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。

// 示例 1：

// 输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
// 输出：true
// 示例 2：

// 输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
// 输出：false

// 提示：

// m == matrix.length
// n == matrix[i].length
// 1 <= m, n <= 100
// -104 <= matrix[i][j], target <= 104
class Solution
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

// 方法二：两次二分查找
class Solution2
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        auto row = upper_bound(matrix.begin(), matrix.end(), target, [](int value, const vector<int> &row)
                               { return value < row[0]; });
        if (row == matrix.begin()) // matrix[0][0] 就大于 target
            return false;
        --row;
        return binary_search(row->begin(), row->end(), target);
    }
};

// 方法三：while实现
class Solution3
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        int left = 0;
        int right = (matrix.size() * matrix[0].size()) - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            int midValue = matrix[mid / matrix[0].size()][mid % matrix[0].size()];
            if (midValue == target)
                return true;
            else if (midValue < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return false;
    }
};