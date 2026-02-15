package hot100;

import java.util.Arrays;

// 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

// 请注意 ，必须在不复制数组的情况下原地对数组进行操作。
public class Solution0283 {
    public void moveZeroes(int[] nums) {
        int cur = 0; // 当前非零元素应该放置的位置
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] != 0) {
                nums[cur] = nums[i];
                if (cur != i) {
                    nums[i] = 0; // 将当前位置设置为0
                }
                cur++;
            }
        }
    }

    public static void main(String[] args) {
        Solution0283 solution0283 = new Solution0283();
        int[] nums = new int[] { 0, 1, 0, 3, 12 };
        solution0283.moveZeroes(nums);
        System.out.println(Arrays.toString(nums));
    }
}
