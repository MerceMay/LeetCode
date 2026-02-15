#include <vector>
using namespace std;
// 给你一个整数数组 nums ，其中元素已经按 升序 排列，请你将其转换为一棵 平衡 二叉搜索树。
class Solution
{
private:
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

public:
    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        return createTree(nums, 0, nums.size() - 1);
    }

private:
    TreeNode *createTree(vector<int> &nums, int left, int right)
    {
        if (left > right)
            return nullptr;
        int mid = left + (right - left) / 2;
        TreeNode *node = new TreeNode(nums[mid]);
        node->left = createTree(nums, left, mid - 1);
        node->right = createTree(nums, mid + 1, right);
        return node;
    }
};