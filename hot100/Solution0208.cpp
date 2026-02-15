#include <string>
#include <array>
#include <memory>
using namespace std;
// Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补全和拼写检查。

// 请你实现 Trie 类：

// Trie() 初始化前缀树对象。
// void insert(String word) 向前缀树中插入字符串 word 。
// boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
// boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。

// 示例：

// 输入
// ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
// [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
// 输出
// [null, null, true, false, true, null, true]

// 解释
// Trie trie = new Trie();
// trie.insert("apple");
// trie.search("apple");   // 返回 True
// trie.search("app");     // 返回 False
// trie.startsWith("app"); // 返回 True
// trie.insert("app");
// trie.search("app");     // 返回 True

// 提示：

// 1 <= word.length, prefix.length <= 2000
// word 和 prefix 仅由小写英文字母组成
// insert、search 和 startsWith 调用次数 总计 不超过 3 * 104 次

class Trie
{
private:
    class TrieNode
    {
    public:
        int pass;
        int end;
        array<unique_ptr<TrieNode>, 26> nexts;
        TrieNode() : pass(0), end(0) {}
    };
    unique_ptr<TrieNode> root = make_unique<TrieNode>();

public:
    Trie()
    {
    }

    void insert(string word)
    {
        if (word.empty())
            return;

        auto node = root.get();
        node->pass++;
        for (char c : word)
        {
            int index = c - 'a';
            if (!node->nexts[index])
                node->nexts[index] = make_unique<TrieNode>();
            node = node->nexts[index].get();
            node->pass++;
        }
        node->end++;
    }

    int search(string word)
    {
        if (word.empty())
            return 0;
        auto node = root.get();
        for (char c : word)
        {
            int index = c - 'a';
            if (!node->nexts[index])
                return 0;
            node = node->nexts[index].get();
        }
        return node->end;
    }

    int startsWith(string prefix)
    {
        if (prefix.empty())
            return root->pass;
        auto node = root.get();
        for (char c : prefix)
        {
            int index = c - 'a';
            if (!node->nexts[index])
                return 0;
            node = node->nexts[index].get();
        }
        return node->pass;
    }

    bool deleteWord(string word)
    {
        if (search(word) == 0)
            return false;

        auto node = root.get();
        node->pass--;
        for (char c : word)
        {
            int index = c - 'a';
            TrieNode *nextNode = node->nexts[index].get(); // 这里提前获取下一指针，然后减少计数
            nextNode->pass--;
            if (nextNode->pass == 0)
            {
                node->nexts[index].reset();
                return true; // 直接返回，后续的节点会被智能指针自动释放
            }
            node = nextNode;
        }
        node->end--; // 如果执行到这里，说明if分支没有执行，不会出现问题
        return true;
    }

    bool empty()
    {
        return root->pass == 0;
    }

    int size()
    {
        return root->pass;
    }
};