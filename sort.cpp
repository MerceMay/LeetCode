#include <vector>
#include <cstdlib>

void selectionSort(std::vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j)
        {
            minIndex = (arr[j] < arr[minIndex]) ? j : minIndex;
        }
        std::swap(arr[i], arr[minIndex]);
    }
}

void bubbleSort(std::vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(std::vector<int> &arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--)
        {
            std::swap(arr[j], arr[j + 1]);
        }
    }
}

void mergeSort(std::vector<int> &arr, int left, int right)
{
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    // merge
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right)
    {
        temp[k++] = (arr[i] <= arr[j]) ? arr[i++] : arr[j++];
    }
    while (i <= mid)
    {
        temp[k++] = arr[i++];
    }
    while (j <= right)
    {
        temp[k++] = arr[j++];
    }
    for (int p = 0; p < temp.size(); p++)
    {
        arr[left + p] = temp[p];
    }
}

void quickSort(std::vector<int> &arr, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    std::swap(arr[left], arr[left + rand() % (right - left + 1)]);
    int pivot = arr[left];

    int less = left;
    int great = right;
    int i = left + 1;

    while (i < great)
    {
        if (arr[i] < pivot)
        {
            std::swap(arr[i], arr[less]);
            less++;
            i++;
        }
        else if (arr[i] > pivot)
        {
            std::swap(arr[i], arr[great]);
            great--;
        }
        else
        {
            i++;
        }
    }
    quickSort(arr, left, i - 1);
    quickSort(arr, great + 1, right);
}

int main()
{
    std::vector<int> vec = {5, 3, 8, 1, 4};
}