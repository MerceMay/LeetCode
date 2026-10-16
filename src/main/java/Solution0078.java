import java.util.*;

//给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。
//
//解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

public class Solution0078 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int[] nums = Arrays.stream(line.substring(1, line.length() - 1).split(","))
                .mapToInt(Integer::parseInt)
                .toArray();
        System.out.println(subsets(nums));
        System.out.println(subsets2(nums));
        System.out.println(subsets3(nums));
    }

    public static List<List<Integer>> subsets(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(nums, result, new ArrayList<>(), 0);
        return result;
    }

    private static void backtrack(int[] nums, List<List<Integer>> result, List<Integer> path, int index) {
        result.add(new ArrayList<>(path));
        for (int i = index; i < nums.length; i++) {
            path.add(nums[i]);
            backtrack(nums, result, path, i + 1);
            path.remove(path.size() - 1);
        }
    }

    public static List<List<Integer>> subsets2(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack2(nums, result, new ArrayList<>(), 0);
        return result;
    }

    private static void backtrack2(int[] nums, List<List<Integer>> result, List<Integer> path, int index) {
        if (index == nums.length) {
            result.add(new ArrayList<>(path));
            return;
        }
        path.add(nums[index]);
        backtrack2(nums, result, path, index + 1);
        path.remove(path.size() - 1);
        backtrack2(nums, result, path, index + 1);
    }

    public static List<List<Integer>> subsets3(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        List<Integer> path = new ArrayList<>();
        int n = nums.length;
        for (int mask = 0; mask < (1 << n); mask++) {
            path.clear();
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) != 0) {
                    path.add(nums[i]);
                }
            }
            result.add(new ArrayList<>(path));
        }
        return result;
    }
}
