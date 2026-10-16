import java.util.*;

//中位数是有序整数列表中的中间值。如果列表的大小是偶数，则没有中间值，中位数是两个中间值的平均值。
//
//例如 arr = [2,3,4] 的中位数是 3 。
//例如 arr = [2,3] 的中位数是 (2 + 3) / 2 = 2.5 。
//实现 MedianFinder 类:
//
//MedianFinder() 初始化 MedianFinder 对象。
//
//void addNum(int num) 将数据流中的整数 num 添加到数据结构中。
//
//double findMedian() 返回到目前为止所有元素的中位数。与实际答案相差 10-5 以内的答案将被接受。

public class Solution0295 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        String line1 = sc.nextLine();
        String line2 = sc.nextLine();

        String[] operations = Arrays.stream(
                        line1.substring(1, line1.length() - 1).split(","))
                .map(s -> s.trim().replace("\"", ""))
                .toArray(String[]::new);

        int[] argList = Arrays.stream(
                        line2.replaceAll("[\\[\\]]", "").split(","))
                .map(String::trim)
                .filter(s -> !s.isEmpty())
                .mapToInt(Integer::parseInt)
                .toArray();

        MedianFinder medianFinder = null;
        int argIndex = 0;

        System.out.print("[");
        for (int i = 0; i < operations.length; i++) {
            if (i > 0) {
                System.out.print(", ");
            }

            switch (operations[i]) {
                case "MedianFinder":
                    medianFinder = new MedianFinder();
                    System.out.print("null");
                    break;

                case "addNum":
                    medianFinder.addNum(argList[argIndex++]);
                    System.out.print("null");
                    break;

                case "findMedian":
                    System.out.print(medianFinder.findMedian());
                    break;
            }
        }
        System.out.print("]");
    }

    public static class MedianFinder {
        private PriorityQueue<Integer> minHeap;
        private PriorityQueue<Integer> maxHeap;

        public MedianFinder() {
            minHeap = new PriorityQueue<>();
            maxHeap = new PriorityQueue<>(Comparator.reverseOrder());
        }

        public void addNum(int num) {
            if (maxHeap.isEmpty() || num < maxHeap.peek()) {
                maxHeap.offer(num);
                if (maxHeap.size() > minHeap.size() + 1) {
                    minHeap.offer(maxHeap.poll());
                }
            } else {
                minHeap.offer(num);
                if (minHeap.size() > maxHeap.size()) {
                    maxHeap.offer(minHeap.poll());
                }
            }
        }

        public double findMedian() {
            if (maxHeap.size() > minHeap.size()) {
                return maxHeap.peek();
            }
            return (maxHeap.peek() + minHeap.peek()) / 2.0;
        }
    }
}
