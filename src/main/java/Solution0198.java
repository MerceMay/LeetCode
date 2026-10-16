import java.util.*;

//你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
//
//给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。

public class Solution0198 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int[] nums = Arrays.stream(line.substring(1, line.length() - 1).split(","))
                .mapToInt(Integer::parseInt)
                .toArray();
        System.out.println(rob(nums));
    }

    public static int rob(int[] nums) {
        int[] cache = new int[nums.length];
        for (int i = 0; i < nums.length; i++) {
            if (i == 0) {
                cache[0] = nums[0];
            } else if (i == 1) {
                cache[1] = Math.max(cache[0], nums[1]);
            } else {
                cache[i] = Math.max(cache[i - 1], cache[i - 2] + nums[i]);
            }
        }
        return cache[nums.length - 1];
    }

    public static int rob2(int[] nums) {
        if (nums.length == 1) {
            return nums[0];
        }
        int pre2 = nums[0], pre1 = Math.max(nums[0], nums[1]);
        for (int i = 2; i < nums.length; i++) {
            int current = Math.max(pre1, pre2 + nums[i]);
            pre2 = pre1;
            pre1 = current;
        }
        return pre1;
    }
}
