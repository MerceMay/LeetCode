import java.util.*;

//给定一个长度为 n 的 0 索引整数数组 nums。初始位置在下标 0。
//
//每个元素 nums[i] 表示从索引 i 向后跳转的最大长度。换句话说，如果你在索引 i 处，你可以跳转到任意 (i + j) 处：
//
//0 <= j <= nums[i] 且
//i + j < n
//
//返回到达 n - 1 的最小跳跃次数。测试用例保证可以到达 n - 1。

public class Solution0045 {
    public int jump(int[] nums) {
        int step = 0;
        int farthest = 0;
        int prevFarthest = 0;
        for (int i = 0; i < nums.length - 1; i++) {
            farthest = Math.max(farthest, i + nums[i]);
            if (i == prevFarthest) {
                prevFarthest = farthest;
                step++;
            }
        }
        return step;
    }

    public int jump2(int[] nums) {
        int steps = 0;
        int pos = nums.length - 1;
        while (pos > 0) {
            for (int i = 0; i < pos; i++) {
                if (i + nums[i] >= pos) {
                    pos = i;
                    steps++;
                    break;
                }
            }
        }
        return steps;
    }
}
