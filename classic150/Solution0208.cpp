#include <string>
#include <memory>
#include <array>
using namespace std;
// Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补全和拼写检查。

// 请你实现 Trie 类：

// Trie() 初始化前缀树对象。
// void insert(String word) 向前缀树中插入字符串 word 。
// boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
// boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。
class Trie
{
private:
    class TrieNode
    {
    public:
        int pass = 0;
        int end = 0;
        array<unique_ptr<TrieNode>, 26> nexts = {};
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
        TrieNode *node = root.get();
        node->pass++;
        for (char ch : word)
        {
            int index = ch - 'a';
            if (!node->nexts[index])
                node->nexts[index] = make_unique<TrieNode>();
            node = node->nexts[index].get();
            node->pass++;
        }
        node->end++;
    }

    bool search(string word)
    {
        if (word.empty())
            return false;
        TrieNode *node = root.get();
        for (char ch : word)
        {
            int index = ch - 'a';
            if (!node->nexts[index])
                return false;
            node = node->nexts[index].get();
        }
        return node->end > 0;
    }

    bool startsWith(string prefix)
    {
        if (prefix.empty())
            return false;
        TrieNode *node = root.get();
        for (char ch : prefix)
        {
            int index = ch - 'a';
            if (!node->nexts[index])
                return false;
            node = node->nexts[index].get();
        }
        return node->pass > 0;
    }

private:
    bool empty()
    {
        return root->pass == 0;
    }

    int size()
    {
        return root->pass;
    }
};