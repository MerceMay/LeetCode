package hot100;

// 给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。

// 请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。

// 思考思路：
// 使用一个额外的Boolean数组来标记。
// 如果把额外数组的标记信息存储在原数组中，即原数组的元素需要进行标记
// 标记可以是正负号或者元素值和索引的关系等
// 正负号无法区分标记后的元素和原数组中的负数，所以使用元素值和索引的关系来标记
// 对于超出范围的元素，直接忽略掉
// 对于交换过来的值，如果仍然不在正确的位置上，继续交换，直到所有元素都在正确的位置上或者无法交换为止
// 对于交换过来的值和当前元素相同，说明存在重复元素，直接跳过交换
// 虽然存在循环交换，但是每个元素交换到正确位置后就不再参与交换，所以总的时间复杂度仍然是O(n)
public class Solution0041 {
    public int firstMissingPositive(int[] nums) {
        int n = nums.length;
        for (int i = 0; i < n; i++) {
            while (nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1]) {
                int temp = nums[i];
                nums[i] = nums[temp - 1];
                nums[temp - 1] = temp;
            }
        }
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i + 1;
            }
        }
        return n + 1;
    }

    public static void main(String[] args) {
        int[] nums = { 1, 2, 0 };
        int result = new Solution0041().firstMissingPositive(nums);
        System.out.println(result);
    }
}
