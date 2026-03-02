package anew;

import java.util.ArrayList;
import java.util.List;

// 给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，并以列表形式返回。你可以按 任意顺序 返回这些组合。

// candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。 

// 对于给定的输入，保证和为 target 的不同组合数少于 150 个。

public class Solution0039 {
    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        List<List<Integer>> res = new ArrayList<>();
        List<Integer> path = new ArrayList<>();
        backtrack(candidates, target, 0, res, path);
        return res;
    }

    private void backtrack(int[] candidates, int target, int index, List<List<Integer>> res, List<Integer> path) {
        if (target == 0) {
            res.add(new ArrayList<>(path));
            return;
        }
        if (index == candidates.length || target < 0) {
            return;
        }
        path.add(candidates[index]);
        backtrack(candidates, target - candidates[index], index, res, path);
        path.remove(path.size() - 1);
        backtrack(candidates, target, index + 1, res, path);
    }

    public static void main(String[] args) {
        Solution0039 solution = new Solution0039();
        List<List<Integer>> ans = solution.combinationSum(new int[] { 2, 3, 6, 7 }, 7);
        System.out.println(ans);
    }
}
