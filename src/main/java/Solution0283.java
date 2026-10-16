import java.util.*;

//给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
//
//请注意 ，必须在不复制数组的情况下原地对数组进行操作。

public class Solution0283 {
    public void moveZeros(int[] nums) {
        int curIndex = 0;
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] != 0) {
                int temp = nums[i];
                nums[i] = nums[curIndex];
                nums[curIndex] = temp;
                curIndex++;
            }
        }
    }
}
