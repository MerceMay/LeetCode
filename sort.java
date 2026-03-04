import java.util.Random;

public class sort {
    public void bubbleSort(int[] nums) {
        for (int i = 0; i < nums.length - 1; i++) {
            for (int j = 0; j < nums.length - 1 - i; j++) {
                if (nums[j] > nums[j + 1]) {
                    int temp = nums[j];
                    nums[j] = nums[j + 1];
                    nums[j + 1] = temp;
                }
            }
        }
    }

    public void selectionSort(int[] nums) {
        for (int i = 0; i < nums.length - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < nums.length; j++) {
                if (nums[j] < nums[minIndex]) {
                    minIndex = j;
                }
            }
            int temp = nums[i];
            nums[i] = nums[minIndex];
            nums[minIndex] = temp;
        }
    }

    public void insertionSort(int[] nums) {
        for (int i = 1; i < nums.length; i++) {
            int key = nums[i];
            int j = i - 1;
            while (j >= 0 && nums[j] > key) {
                nums[j + 1] = nums[j];
                j--;
            }
            nums[j + 1] = key;
        }
    }

    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    public void quickSort(int[] nums, String method) {
        if (method.equalsIgnoreCase("Lomuto")) { // 单向快慢指针
            quickSortLomuto(nums, 0, nums.length - 1);
        } else if (method.equalsIgnoreCase("Hoare")) { // 双向扫描指针
            quickSortHoare(nums, 0, nums.length - 1);
        } else if (method.equalsIgnoreCase("3-way")) { // 三路快排
            quickSort3Way(nums, 0, nums.length - 1);
        }
    }

    private void quickSortLomuto(int[] nums, int left, int right) {
        if (left < right) {
            int p = partitionLomuto(nums, left, right);
            quickSortLomuto(nums, left, p - 1);
            quickSortLomuto(nums, p + 1, right);
        }
    }

    private int partitionLomuto(int[] nums, int left, int right) {
        int pivotIndex = left + new Random().nextInt(right - left + 1);
        int pivot = nums[pivotIndex];
        swap(nums, pivotIndex, right); // 将基准元素移到末尾
        int slow = left; // 慢指针：指向第一个大于等于基准值的位置，或者说是小于区域的下一个位置
        for (int i = left; i < right; i++) { // 快指针：扫描整个数组
            if (nums[i] < pivot) {
                swap(nums, i, slow);
                slow++;
            }
        }
        swap(nums, slow, right); // 将基准元素放回正确的位置
        return slow; // 返回基准元素的最终位置
    }

    private void quickSortHoare(int[] nums, int left, int right) {
        if (left < right) {
            // Hoare 分区方案返回的分区点不一定是基准元素的位置
            // 它的含义是：[left..p] 里的数都 <= [p+1..right] 里的数
            int p = partitionHoare(nums, left, right);
            quickSortHoare(nums, left, p);
            quickSortHoare(nums, p + 1, right);
        }
    }

    private int partitionHoare(int[] nums, int left, int right) {
        int pivotIndex = left + new Random().nextInt(right - left + 1);
        swap(nums, pivotIndex, left); // 将基准元素移到开头

        int pivot = nums[left];
        int i = left - 1; // i 从左向右扫描，初始位置在基准元素的左边
        int j = right + 1; // j 从右向左扫描，初始位置在数组的右边
        while (true) {
            do {
                i++;
            } while (nums[i] < pivot);
            do {
                j--;
            } while (nums[j] > pivot);
            if (i >= j) {
                return j; // <= pivot 区域的最后一个元素的索引
            }
            swap(nums, i, j);
        }
    }

    private void quickSort3Way(int[] nums, int left, int right) {
        if (left >= right) {
            return;
        }
        int pivotIndex = left + new Random().nextInt(right - left + 1);
        swap(nums, pivotIndex, left); // 将基准元素移到开头
        int pivot = nums[left];
        int lt = left; // [left...lt-1] < pivot
        int i = left + 1; // [lt...i-1] == pivot
        int gt = right; // [gt+1...right] > pivot
        while (i <= gt) {
            if (nums[i] < pivot) {
                swap(nums, lt++, i++);
            } else if (nums[i] > pivot) {
                swap(nums, i, gt--); // 注意：i 不需要增加，因为交换过来的元素还没有比较过
            } else {
                i++;
            }
        }
        quickSort3Way(nums, left, lt - 1);
        quickSort3Way(nums, gt + 1, right);
    }

    public void mergeSort(int[] nums, int left, int right) {
        if (left >= right) {
            return;
        }
        int mid = left + (right - left) / 2;
        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);
        merge(nums, left, mid, right);
    }

    private void merge(int[] nums, int left, int mid, int right) {
        int[] temp = new int[right - left + 1];
        int i = left, j = mid + 1, k = 0;
        while (i <= mid && j <= right) {
            if (nums[i] <= nums[j]) {
                temp[k++] = nums[i++];
            } else {
                temp[k++] = nums[j++];
            }
        }
        while (i <= mid) {
            temp[k++] = nums[i++];
        }
        while (j <= right) {
            temp[k++] = nums[j++];
        }
        System.arraycopy(temp, 0, nums, left, temp.length);
    }

    public void heapSort(int[] nums) {
        int n = nums.length;
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(nums, n, i);
        }
        for (int i = n - 1; i > 0; i--) {
            int temp = nums[0];
            nums[0] = nums[i];
            nums[i] = temp;
            heapify(nums, i, 0);
        }
    }

    private void heapify(int[] nums, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && nums[left] > nums[largest]) {
            largest = left;
        }
        if (right < n && nums[right] > nums[largest]) {
            largest = right;
        }
        if (largest != i) {
            int temp = nums[i];
            nums[i] = nums[largest];
            nums[largest] = temp;
            heapify(nums, n, largest);
        }
    }
}
