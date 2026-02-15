#include <unordered_map>
using namespace std;
// 请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
// 实现 LRUCache 类：
// LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
// int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
// void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
// 函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。

class LRUCache
{
private:
    struct DLinkedList
    {
        int key;
        int value;
        DLinkedList *prev;
        DLinkedList *next;
        DLinkedList(int key, int value) : key(key), value(value), prev(nullptr), next(nullptr) {}
    };

    DLinkedList *head; // 头部是最久未使用的
    DLinkedList *tail; // 尾部是最新使用的
    unordered_map<int, DLinkedList *> cache;
    int capacity;

public:
    LRUCache(int capacity)
    {
        this->capacity = capacity;
        head = new DLinkedList(-1, -1);
        tail = new DLinkedList(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key)
    {
        if (cache.find(key) == cache.end())
            return -1;
        DLinkedList *node = cache[key];
        // 把node移动到尾部
        node->prev->next = node->next;
        node->next->prev = node->prev;
        node->next = tail;
        tail->prev->next = node;
        node->prev = tail->prev;
        tail->prev = node;
        return node->value;
    }

    void put(int key, int value)
    {
        if (cache.count(key)) // 存在只需要修改即可
        {
            DLinkedList *node = cache[key];
            node->value = value;
            // 把node移动到尾部
            node->prev->next = node->next;
            node->next->prev = node->prev;
            node->next = tail;
            tail->prev->next = node;
            node->prev = tail->prev;
            tail->prev = node;
        }
        else // 不存在，首先检查是否超过容量
        {
            if (cache.size() == capacity)
            {
                // 删除头部元素
                DLinkedList *toDelete = head->next;
                head->next = toDelete->next;
                toDelete->next->prev = head;
                cache.erase(toDelete->key);
                delete toDelete;
            }
            // 插入新元素
            DLinkedList *newNode = new DLinkedList(key, value);
            cache[key] = newNode;
            tail->prev->next = newNode;
            newNode->prev = tail->prev;
            tail->prev = newNode;
            newNode->next = tail;
        }
    }
};