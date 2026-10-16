import java.util.*;

//给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。

public class Solution0046 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int[] nums = Arrays.stream(line.substring(1, line.length() - 1).split(","))
                .mapToInt(Integer::parseInt)
                .toArray();
        System.out.println(permute(nums));
        System.out.println(permute2(nums));
        System.out.println(permute3(nums));
        System.out.println(permute4(nums));
    }

    public static List<List<Integer>> permute(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        boolean[] used = new boolean[nums.length];
        dfs(nums, result, new ArrayList<>(), used);
        return result;
    }

    private static void dfs(int[] nums, List<List<Integer>> result, List<Integer> path, boolean[] used) {
        if (path.size() == nums.length) {
            result.add(new ArrayList<>(path));
            return;
        }
        for (int i = 0; i < nums.length; i++) {
            if (used[i]) {
                continue;
            }
            path.add(nums[i]);
            used[i] = true;
            dfs(nums, result, path, used);
            path.remove(path.size() - 1);
            used[i] = false;
        }
    }

    public static List<List<Integer>> permute2(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        record State(List<Integer> path, boolean[] used) {
        }
        Deque<State> stack = new LinkedList<>();
        stack.push(new State(new ArrayList<>(), new boolean[nums.length]));
        while (!stack.isEmpty()) {
            State state = stack.pop();
            List<Integer> path = state.path();
            boolean[] used = state.used();
            if (path.size() == nums.length) {
                result.add(path);
                continue;
            }
            for (int i = 0; i < nums.length; i++) {
                if (used[i]) {
                    continue;
                }
                List<Integer> newPath = new ArrayList<>(path);
                boolean[] newUsed = used.clone();
                newPath.add(nums[i]);
                newUsed[i] = true;
                stack.push(new State(newPath, newUsed));
            }
        }
        return result;
    }


    public static List<List<Integer>> permute3(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        List<Integer> path = new ArrayList<>();
        boolean[] used = new boolean[nums.length];
        record Frame(int i, boolean afterChild) {
        }
        Deque<Frame> stack = new LinkedList<>();
        stack.push(new Frame(0, false));
        while (!stack.isEmpty()) {
            Frame frame = stack.pop();
            int i = frame.i();
            // dfs之后
            if (frame.afterChild()) {
                path.remove(path.size() - 1);
                used[i] = false;
                stack.push(new Frame(i + 1, false)); // for之后是另一个for循环，所以需要再次压栈
                continue;
            }
            // for循环结束，即i=nums.length
            if (i == nums.length) {
                continue;
            }
            if (used[i]) {
                stack.push(new Frame(i + 1, false)); // 同理，dfs在for之内，需要再次压栈
                continue;
            }
            path.add(nums[i]);
            used[i] = true;
            if (path.size() == nums.length) {
                result.add(new ArrayList<>(path)); // 叶子节点返回所以需要需要回溯
                path.remove(path.size() - 1);
                used[i] = false;

                stack.push(new Frame(i + 1, false));
            } else {
                stack.push(new Frame(i, true)); // 先压自己回溯
                stack.push(new Frame(0, false)); // 进入下一层dfs
            }
        }
        return result;
    }

    public static List<List<Integer>> permute4(int[] nums) {
        List<List<Integer>> result = new ArrayList<>();
        backtrack(nums, result, 0);
        return result;
    }

    private static void backtrack(int[] nums, List<List<Integer>> result, int index) {
        if (index == nums.length) {
            List<Integer> path = new ArrayList<>();
            for (int num : nums) {
                path.add(num);
            }
            result.add(path);
            return;
        }
        for (int i = index; i < nums.length; i++) {
            swap(nums, index, i);
            backtrack(nums, result, index + 1);
            swap(nums, index, i);
        }
    }

    private static void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
}
