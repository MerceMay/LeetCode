package hot100;

import java.util.List;
import java.util.ArrayList;
// 给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。

// 解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

public class Solution0078 {
    public List<List<Integer>> subsets(int[] nums) {
        List<List<Integer>> res = new ArrayList<>();
        res.add(new ArrayList<>());
        for (int num : nums) {
            int size = res.size();
            for (int i = 0; i < size; i++) {
                List<Integer> list = new ArrayList<>(res.get(i));
                list.add(num);
                res.add(list);
            }
        }
        return res;
    }

    public List<List<Integer>> subsets2(int[] nums) {
        List<List<Integer>> res = new ArrayList<>();
        int n = nums.length;
        for (int i = 0; i < (1 << n); i++) {
            List<Integer> list = new ArrayList<>();
            for (int j = 0; j < n; j++) {
                if ((i & (1 << j)) != 0) {
                    list.add(nums[j]);
                }
            }
            res.add(list);
        }
        return res;
    }

    public List<List<Integer>> subsets3(int[] nums) {
        List<List<Integer>> res = new ArrayList<>();
        backtrack(nums, 0, new ArrayList<>(), res);
        return res;
    }

    private void backtrack(int[] nums, int start, List<Integer> path, List<List<Integer>> res) {
        if (start == nums.length) {
            res.add(new ArrayList<>(path));
            return;
        }
        path.add(nums[start]);
        backtrack(nums, start + 1, path, res);
        path.remove(path.size() - 1);
        backtrack(nums, start + 1, path, res);
    }

    public static void main(String[] args) {
        Solution0078 solution = new Solution0078();
        int[] nums = { 1, 2, 3 };
        List<List<Integer>> res = solution.subsets(nums);
        System.out.println(res);

        List<List<Integer>> res2 = solution.subsets2(nums);
        System.out.println(res2);

        List<List<Integer>> res3 = solution.subsets3(nums);
        System.out.println(res3);
    }
}
