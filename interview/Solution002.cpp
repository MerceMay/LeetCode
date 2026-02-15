// 快排
#include <vector>
#include <iostream>
using namespace std;

class Solution
{
public:
    vector<int> sortArray(vector<int> &nums)
    {
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }

private:
    void quickSort(vector<int> &nums, int left, int right)
    {
        if (left >= right)
            return;
        int pivot = partition(nums, left, right);
        quickSort(nums, left, pivot - 1);
        quickSort(nums, pivot + 1, right);
    }

    int partition(vector<int> &nums, int left, int right)
    {
        int pivot = nums[right];
        int i = left - 1;
        for (int j = left; j < right; j++)
        {
            if (nums[j] <= pivot)
            {
                i++;
                swap(nums[i], nums[j]);
            }
        }
        swap(nums[i + 1], nums[right]);
        return i + 1;
    }
};

int main()
{
    Solution s;
    vector<int> nums = {5, 2, 3, 1};
    vector<int> sorted = s.sortArray(nums);
    for (int num : sorted)
        cout << num << " ";
    cout << endl;
    return 0;
}