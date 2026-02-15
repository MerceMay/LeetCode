#include <vector>
#include <functional>
#include <algorithm>

template <typename T, typename Compare = std::less<T>>
class Heap
{
private:
    std::vector<T> data;
    Compare comp;

public:
    Heap() = default;
    Heap(Compare c) : comp(c) {}

    void push(const T &value)
    {
        data.push_back(value);
        sift_up(data.size() - 1);
    }

    void pop()
    {
        if (empty())
            return;
        std::swap(data.front(), data.back());
        data.pop_back();
        if (!empty())
            sift_down(0);
    }

    const T &top() const
    {
        if (empty())
            throw std::out_of_range("Heap is empty");
        return data.front();
    }

    bool empty() const
    {
        return data.empty();
    }

    size_t size() const
    {
        return data.size();
    }

private:
    void sift_up(size_t index)
    {
        while (index > 0)
        {
            size_t parent = (index - 1) / 2;
            if (!comp(data[parent], data[index]))
                break;
            std::swap(data[parent], data[index]);
            index = parent;
        }
    }

    void sift_down(size_t index)
    {
        while (index < data.size())
        {
            size_t left = index * 2 + 1;
            size_t right = index * 2 + 2;
            size_t smallest = index;

            if (left < data.size() && comp(data[smallest], data[left]))
                smallest = left;
            if (right < data.size() && comp(data[smallest], data[right]))
                smallest = right;
            if (smallest == index)
                break;

            std::swap(data[index], data[smallest]);
            index = smallest;
        }
    }
};