#include <list>
#include <unordered_map>
using namespace std;
// 请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
// 实现 LRUCache 类：
// LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
// int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
// void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
// 函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。

// 示例：

// 输入
// ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
// [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
// 输出
// [null, null, null, 1, null, -1, null, -1, 3, 4]

// 解释
// LRUCache lRUCache = new LRUCache(2);
// lRUCache.put(1, 1); // 缓存是 {1=1}
// lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
// lRUCache.get(1);    // 返回 1
// lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
// lRUCache.get(2);    // 返回 -1 (未找到)
// lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
// lRUCache.get(1);    // 返回 -1 (未找到)
// lRUCache.get(3);    // 返回 3
// lRUCache.get(4);    // 返回 4

// 提示：

// 1 <= capacity <= 3000
// 0 <= key <= 10000
// 0 <= value <= 105
// 最多调用 2 * 105 次 get 和 put
// 方法一：使用容器std::list
class LRUCache
{
private:
    int capacity;
    // 使用双向链表和哈希表来实现 LRU 缓存
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> cacheMap;

public:
    LRUCache(int capacity)
    {
        this->capacity = capacity;
    }

    int get(int key)
    {
        auto it = cacheMap.find(key);
        if (it == cacheMap.end())
            return -1;
        // 移动到链表头部
        cache.splice(cache.begin(), cache, it->second);
        return it->second->second; // 返回值
    }

    void put(int key, int value)
    {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end())
        {
            // 更新值并移动到链表头部
            it->second->second = value;
            cache.splice(cache.begin(), cache, it->second);
        }
        else
        {
            // 如果不存在
            if (cache.size() == capacity)
            {
                cacheMap.erase(cache.back().first); // 删除最久未使用的元素
                cache.pop_back();
            }
            // 插入新元素
            cache.push_front({key, value});
            cacheMap[key] = cache.begin();
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// 方法二：手动实现双向链表
class LRUCache2
{
private:
    struct DLinkedList
    {
        int key;
        int value;
        DLinkedList *prev;
        DLinkedList *next;
        DLinkedList(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };
    DLinkedList *head;
    DLinkedList *tail;
    unordered_map<int, DLinkedList *> cacheMap;
    int capacity;

public:
    LRUCache2(int capacity)
    {
        this->capacity = capacity;
        head = new DLinkedList(0, 0);
        tail = new DLinkedList(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key)
    {
        auto it = cacheMap.find(key);
        if (it == cacheMap.end())
        {
            return -1;
        }
        // 移动到链表头部
        moveToHead(it->second);
        return it->second->value;
    }

    void put(int key, int value)
    {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end())
        {
            it->second->value = value;
            moveToHead(it->second);
        }
        else
        {
            if (cacheMap.size() == capacity)
            {
                DLinkedList *tailNode = removeTail();
                cacheMap.erase(tailNode->key);
                delete tailNode; // 删除末尾节点，防止内存泄漏
            }
            DLinkedList *newNode = new DLinkedList(key, value);
            cacheMap[key] = newNode;
            addToHead(newNode);
        }
    }

private:
    void addToHead(DLinkedList *node)
    {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void moveToHead(DLinkedList *node)
    {
        removeNode(node);
        addToHead(node);
    }

    DLinkedList *removeTail()
    {
        DLinkedList *tailNode = tail->prev;
        removeNode(tailNode);
        return tailNode;
    }

    void removeNode(DLinkedList *node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
};