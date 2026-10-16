import java.util.*;

//假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
//
//每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

public class Solution0070 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.out.println(climbStairs(n));
        System.out.println(climbStairs2(n));
    }

    public static int climbStairs(int n) {
        int[] cache = new int[n + 1];
        cache[0] = 1;
        cache[1] = 1;
        for (int i = 2; i <= n; i++) {
            cache[i] = cache[i - 1] + cache[i - 2];
        }
        return cache[n];
    }

    public static int climbStairs2(int n) {
        int pre2 = 0, pre1 = 0, result = 1;
        for (int i = 1; i <= n; i++) {
            pre2 = pre1;
            pre1 = result;
            result = pre1 + pre2;
        }
        return result;
    }
}
