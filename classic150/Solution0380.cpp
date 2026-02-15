#include <unordered_map>
#include <vector>
#include <cstdlib>
using namespace std;
// 实现RandomizedSet 类：

// RandomizedSet() 初始化 RandomizedSet 对象
// bool insert(int val) 当元素 val 不存在时，向集合中插入该项，并返回 true ；否则，返回 false 。
// bool remove(int val) 当元素 val 存在时，从集合中移除该项，并返回 true ；否则，返回 false 。
// int getRandom() 随机返回现有集合中的一项（测试用例保证调用此方法时集合中至少存在一个元素）。每个元素应该有 相同的概率 被返回。
// 你必须实现类的所有函数，并满足每个函数的 平均 时间复杂度为 O(1) 。
class RandomizedSet
{
private:
    unordered_map<int, int> valToIndex;
    vector<int> values;

public:
    RandomizedSet()
    {
    }

    bool insert(int val)
    {
        if (valToIndex.count(val))
            return false;
        valToIndex[val] = values.size();
        values.push_back(val);
        return true;
    }

    bool remove(int val)
    {
        if (!valToIndex.count(val))
            return false;
        int index = valToIndex[val];
        int lastVal = values.back();
        values[index] = lastVal;          // 用最后一个元素覆盖要删除的元素
        valToIndex[lastVal] = index;      // 更新最后一个元素的索引
        values.pop_back();                 // 删除最后一个元素
        valToIndex.erase(val);             // 删除映射
        return true;
    }

    int getRandom()
    {
        return values[rand() % values.size()];
    }
};