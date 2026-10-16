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
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int[] nums = Arrays.stream(line.substring(1, line.length() - 1).split(","))
                .mapToInt(Integer::parseInt)
                .toArray();
        System.out.println(jump(nums));
        System.out.println(jump2(nums));
    }

    public static int jump(int[] nums) {
        int steps = 0;
        int farthest = 0;
        int curFarthest = 0;
        for (int i = 0; i < nums.length; i++) {
            farthest = Math.max(farthest, i + nums[i]);
            if (i == curFarthest) {
                curFarthest = farthest;
                steps++;
            }
        }
        return steps;
    }

    public static int jump2(int[] nums) {
        int steps = 0;
        int position = nums.length - 1;
        while (position > 0) {
            for (int i = 0; i < position; i++) {
                if (i + nums[i] >= position) {
                    position = i;
                    steps++;
                    break;
                }
            }
        }
        return steps;
    }
}
