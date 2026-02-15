#include <string>
#include <memory>
#include <array>
using namespace std;
// 请你设计一个数据结构，支持 添加新单词 和 查找字符串是否与任何先前添加的字符串匹配 。

// 实现词典类 WordDictionary ：

// WordDictionary() 初始化词典对象
// void addWord(word) 将 word 添加到数据结构中，之后可以对它进行匹配
// bool search(word) 如果数据结构中存在字符串与 word 匹配，则返回 true ；否则，返回  false 。word 中可能包含一些 '.' ，每个 . 都可以表示任何一个字母。
class WordDictionary
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
    WordDictionary()
    {
    }

    void addWord(string word)
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
        return searchIn(root.get(), word, 0);
    }

    bool searchIn(TrieNode *node, const string &word, int index)
    {
        if (index == word.size())
            return node->end > 0;
        char ch = word[index];
        if (ch == '.')
        {
            for (int i = 0; i < 26; i++)
            {
                if (node->nexts[i] && searchIn(node->nexts[i].get(), word, index + 1))
                    return true;
            }
            return false;
        }
        else
        {
            int nextIndex = ch - 'a';
            if (!node->nexts[nextIndex])
                return false;
            return searchIn(node->nexts[nextIndex].get(), word, index + 1);
        }
    }
};