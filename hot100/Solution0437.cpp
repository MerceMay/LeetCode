#include <unordered_map>
using namespace std;
// 给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。

// 路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

// 示例 1：

// 输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
// 输出：3
// 解释：和等于 8 的路径有 3 条，如图所示。
// 示例 2：

// 输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
// 输出：3

// 提示:

// 二叉树的节点个数的范围是 [0,1000]
// -109 <= Node.val <= 109
// -1000 <= targetSum <= 1000
// 方法一：前序遍历每个节点，每个节点再作为路径头递归
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

    int count = 0;
    long long target = 0;

public:
    int pathSum(TreeNode *root, int targetSum)
    {
        target = targetSum;
        preOrder(root);
        return count;
    }

private:
    void preOrder(TreeNode *node)
    {
        if (!node)
            return;
        addToPath(node, 0);
        preOrder(node->left);
        preOrder(node->right);
    }

    void addToPath(TreeNode *node, long long currentSum)
    {
        if (!node)
            return;
        currentSum += node->val;
        if (currentSum == target)
            count++;
        // 从当前节点开始的路径
        addToPath(node->left, currentSum);
        addToPath(node->right, currentSum);
    }
};
// 方法二：每个节点作为路径头+左节点作为中途点+右节点作为中途点
class Solution2
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
    int pathSum(TreeNode *root, int targetSum)
    {
        if (!root)
            return 0;
        int result = rootSum(root, (long long) targetSum);
        result += pathSum(root->left, targetSum);
        result += pathSum(root->right, targetSum);
        return result;
    }

private:
    int rootSum(TreeNode *node, long long targetSum)
    {
        if (!node)
            return 0;
        int count = 0;
        if (node->val == targetSum)
            count++;
        count += rootSum(node->left, targetSum - node->val);
        count += rootSum(node->right, targetSum - node->val);
        return count;
    }
};

// 方法三：前缀和+哈希表。
// 假设现在遍历到了current，而存在某一个节点q，使得q到current的路径和为targetSum。
// (根到current的前缀和) - targetSum = (根到q的前缀和)
// 我们并不关心q具体在哪？我们只关心存在多少个(根到q的前缀和)
class Solution3
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

    unordered_map<long long, int> prefixSumCount; // 存储前缀和及其出现次数
    int target;

public:
    int pathSum(TreeNode *node, int targetSum)
    {
        target = targetSum;
        prefixSumCount[0] = 1; // 前缀和为0出现一次
        return dfs(node, 0);
    }

private:
    int dfs(TreeNode *node, long long currentSum)
    {
        if (!node)
            return 0;

        currentSum += node->val; // 更新当前前缀和

        int result = prefixSumCount.count(currentSum - target) ? prefixSumCount[currentSum - target] : 0; // 查找当前前缀和减去目标值的次数，即有多少个p

        prefixSumCount[currentSum]++; // 记录当前前缀和出现次数，这一步不能出现在result之前

        result += dfs(node->left, currentSum); // 递归左子树
        result += dfs(node->right, currentSum); // 递归右子树

        prefixSumCount[currentSum]--; // 回溯，撤销当前前缀和的记录。因为一个节点访问完了其所有子节点，则要回其父节点，父节点再去访问右子树，因此，这个节点不会再出现在他父亲的路线中了
        return result;
    }
};