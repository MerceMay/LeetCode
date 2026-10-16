import java.util.*;

//以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。

public class Solution0056 {
    public static int[][] merge(int[][] intervals) {
        if (intervals.length == 0) {
            return new int[0][2];
        }
        Arrays.sort(intervals, Comparator.comparingInt(a -> a[0]));

        List<int[]> result = new ArrayList<>();
        int[] current = intervals[0];
        for (int[] interval : intervals) {
            if (current[0] < interval[0]) {
                result.add(current);
                current = interval;
            } else {
                current[1] = Math.max(current[1], interval[1]);
            }
        }
        result.add(current);
        return result.toArray(int[][]::new);
    }
}
