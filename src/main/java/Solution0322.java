import java.util.*;

//给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。
//
//计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。
//
//你可以认为每种硬币的数量是无限的。

public class Solution0322 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int amount = sc.nextInt();
        int[] coins = Arrays.stream(line.substring(1, line.length() - 1).split(","))
                .map(String::trim)
                .mapToInt(Integer::parseInt)
                .toArray();
        System.out.println(coinChange(coins, amount));
        System.out.println(coinChange2(coins, amount));
    }

    // 自底向上
    public static int coinChange(int[] coins, int amount) {
        int[] cache = new int[amount + 1];
        Arrays.fill(cache, amount + 1);
        cache[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (coin <= i) {
                    cache[i] = Math.min(cache[i], cache[i - coin] + 1);
                }
            }
        }
        return cache[amount] > amount ? -1 : cache[amount];
    }

    // 自顶向下、记忆化搜索
    public static int coinChange2(int[] coins, int amount) {
        if (amount < 1) {
            return 0;
        }
        return dfs(coins, amount, new int[amount + 1]);
    }

    private static int dfs(int[] coins, int rest, int[] cache) {
        if (rest < 0) {
            return -1;
        }
        if (rest == 0) {
            return 0;
        }
        if (cache[rest] != 0) {
            return cache[rest];
        }
        int min = Integer.MAX_VALUE;
        for (int coin : coins) {
            int result = dfs(coins, rest - coin, cache);
            if (result >= 0 && result < min) {
                min = result + 1;
            }
        }
        cache[rest] = min == Integer.MAX_VALUE ? -1 : min;
        return cache[rest];
    }
}
