import java.util.*;

//给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，并以列表形式返回。你可以按 任意顺序 返回这些组合。
//
//candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。
//
//对于给定的输入，保证和为 target 的不同组合数少于 150 个。

public class Solution0039 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int target = sc.nextInt();
        int[] candidates = Arrays.stream(line.substring(1, line.length() - 1).split(","))
                .mapToInt(Integer::parseInt)
                .toArray();
        System.out.println(combinationSum(candidates, target));
    }

    public static List<List<Integer>> combinationSum(int[] candidates, int target) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack2(candidates, result, new ArrayList<>(), 0, target);
        return result;
    }

    private static void backtrack(int[] candidates, List<List<Integer>> result, List<Integer> path, int index, int target) {
        if (target == 0) {
            result.add(new ArrayList<>(path));
            return;
        }
        if (target < 0) {
            return;
        }
        for (int i = index; i < candidates.length; i++) {
            path.add(candidates[i]);
            backtrack(candidates, result, path, i, target - candidates[i]);
            path.remove(path.size() - 1);
        }
    }

    private static void backtrack2(int[] candidates, List<List<Integer>> result, List<Integer> path, int index, int target) {
        if (index == candidates.length) {
            return;
        }
        if (target == 0) {
            result.add(new ArrayList<>(path));
            return;
        }
        if (target < 0) {
            return;
        }
        path.add(candidates[index]);
        backtrack2(candidates, result, path, index, target - candidates[index]);
        path.remove(path.size() - 1);
        backtrack2(candidates, result, path, index + 1, target);
    }
}
