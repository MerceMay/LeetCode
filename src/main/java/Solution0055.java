import java.util.*;

//给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。
//
//判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。

public class Solution0055 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int[] nums = Arrays.stream(line.substring(1, line.length() - 1).split(","))
                .mapToInt(Integer::parseInt)
                .toArray();
        System.out.println(canJump(nums));
    }

    public static boolean canJump(int[] nums) {
        int farthest = 0;
        for (int i = 0; i < nums.length; i++) {
            if (i <= farthest) {
                farthest = Math.max(farthest, i + nums[i]);
                if (farthest >= nums.length - 1) {
                    return true;
                }
            }
        }
        return false;
    }
}
