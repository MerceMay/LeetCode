package anew;

import java.util.TreeMap;
import java.util.PriorityQueue;

// 中位数是有序整数列表中的中间值。如果列表的大小是偶数，则没有中间值，中位数是两个中间值的平均值。

// 例如 arr = [2,3,4] 的中位数是 3 。
// 例如 arr = [2,3] 的中位数是 (2 + 3) / 2 = 2.5 。
// 实现 MedianFinder 类:

// MedianFinder() 初始化 MedianFinder 对象。

// void addNum(int num) 将数据流中的整数 num 添加到数据结构中。

// double findMedian() 返回到目前为止所有元素的中位数。与实际答案相差 10-5 以内的答案将被接受。

public class Solution0295 {
    private static class MedianFinder {
        private PriorityQueue<Integer> maxHeap; // 存储较小的一半元素
        private PriorityQueue<Integer> minHeap; // 存储较大的一半元素

        public MedianFinder() {
            maxHeap = new PriorityQueue<>((a, b) -> b - a);
            minHeap = new PriorityQueue<>();
        }

        // 保证两个堆的大小差不超过 1，并且 maxHeap 中的元素都小于等于 minHeap 中的元素
        public void addNum(int num) {
            if (maxHeap.isEmpty() || num <= maxHeap.peek()) {
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
            } else {
                return (maxHeap.peek() + minHeap.peek()) / 2.0;
            }
        }
    }

    private static class MedianFinder2 {
        private TreeMap<Integer, Integer> map; // 存储元素及其出现次数
        private int count; // 记录元素总数
        private int leftKey, leftIndex; // 中位数左边的元素及其索引
        private int rightKey, rightIndex; // 中位数右边的元素及其索引

        public MedianFinder2() {
            map = new TreeMap<>();
            count = 0;
        }

        public void addNum(int num) {
            map.put(num, map.getOrDefault(num, 0) + 1);
            if (count == 0) {
                leftKey = rightKey = num;
                leftIndex = rightIndex = 0;
            } else {
                if ((count & 1) == 1) {
                    if (num < leftKey) {
                        moveLeft(false); // left--;
                    } else {
                        moveRight(true); // right++;
                    }
                } else {
                    if (num > leftKey && num < rightKey) {
                        moveLeft(true);
                        moveRight(false);
                    } else if (num >= rightKey) {
                        moveLeft(true);
                    } else {
                        moveRight(false);
                        leftKey = rightKey;
                        leftIndex = rightIndex;
                    }
                }
            }
            count++;
        }

        public double findMedian() {
            return (leftKey + (double) rightKey) / 2.0;
        }

        private void moveLeft(boolean forward) {
            if (forward) {
                if (leftIndex + 1 < map.get(leftKey)) {
                    leftIndex++;
                } else {
                    leftKey = map.higherKey(leftKey);
                    leftIndex = 0;
                }
            } else {
                if (leftIndex > 0) {
                    leftIndex--;
                } else {
                    leftKey = map.lowerKey(leftKey);
                    leftIndex = map.get(leftKey) - 1;
                }
            }
        }

        private void moveRight(boolean forward) {
            if (forward) {
                if (rightIndex + 1 < map.get(rightKey)) {
                    rightIndex++;
                } else {
                    rightKey = map.higherKey(rightKey);
                    rightIndex = 0;
                }
            } else {
                if (rightIndex > 0) {
                    rightIndex--;
                } else {
                    rightKey = map.lowerKey(rightKey);
                    rightIndex = map.get(rightKey) - 1;
                }
            }
        }
    }

    public static void main(String[] args) {
        MedianFinder medianFinder = new MedianFinder();
        medianFinder.addNum(1); // arr = [1]
        medianFinder.addNum(2); // arr = [1, 2]
        System.out.println(medianFinder.findMedian()); // 返回 1.5 ((1 + 2) / 2)
        medianFinder.addNum(3); // arr = [1, 2, 3]
        System.out.println(medianFinder.findMedian()); // 返回 2.0

        MedianFinder2 medianFinder2 = new MedianFinder2();
        medianFinder2.addNum(1); // arr = [1]
        medianFinder2.addNum(2); // arr = [1, 2]
        System.out.println(medianFinder2.findMedian()); // 返回 1.5 ((1 + 2) / 2)
        medianFinder2.addNum(3); // arr = [1, 2, 3]
        System.out.println(medianFinder2.findMedian()); // 返回 2.0
    }
}
