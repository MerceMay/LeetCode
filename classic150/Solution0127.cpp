#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <unordered_map>
using namespace std;
// 字典 wordList 中从单词 beginWord 到 endWord 的 转换序列 是一个按下述规格形成的序列 beginWord -> s1 -> s2 -> ... -> sk：

// 每一对相邻的单词只差一个字母。
//  对于 1 <= i <= k 时，每个 si 都在 wordList 中。注意， beginWord 不需要在 wordList 中。
// sk == endWord
// 给你两个单词 beginWord 和 endWord 和一个字典 wordList ，返回 从 beginWord 到 endWord 的 最短转换序列 中的 单词数目 。如果不存在这样的转换序列，返回 0 。

// 示例 1：

// 输入：beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
// 输出：5
// 解释：一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog", 返回它的长度 5。
// 示例 2：

// 输入：beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
// 输出：0
// 解释：endWord "cog" 不在字典中，所以无法进行转换。

// 暴力建图 + 单向bfs
class Solution
{
public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        int n = wordList.size();
        vector<vector<int>> adjacencyList(n);
        queue<pair<int, int>> q; // {index,step}
        vector<bool> visited(n);
        int endWordIndex = -1;
        int beginWordIndex = -1;

        // 构建邻接表
        for (int i = 0; i < n; i++)
        {
            if (wordList[i] == endWord)
                endWordIndex = i;
            if (wordList[i] == beginWord)
                beginWordIndex = i;
            for (int j = i + 1; j < n; j++)
            {
                if (isOneCharDiff(wordList[i], wordList[j]))
                {
                    adjacencyList[i].push_back(j);
                    adjacencyList[j].push_back(i);
                }
            }
        }
        if (endWordIndex == -1)
            return 0;
        // beginWord可能不在wordList中，需要创建一个新的节点，并将它与所有只差一个字母的节点相连
        if (beginWordIndex == -1)
        {
            adjacencyList.push_back({});
            for (int i = 0; i < n; i++)
            {
                if (isOneCharDiff(beginWord, wordList[i]))
                {
                    adjacencyList[n].push_back(i);
                    adjacencyList[i].push_back(n);
                    q.push({i, 2});
                    visited[i] = true;
                }
            }
            n++;
        }
        else
        {
            q.push({beginWordIndex, 1});
            visited[beginWordIndex] = true;
        }
        while (!q.empty())
        {
            auto [index, step] = q.front();
            q.pop();
            if (index == endWordIndex)
                return step;
            for (const auto &nextIndex : adjacencyList[index])
            {
                if (!visited[nextIndex])
                {
                    visited[nextIndex] = true;
                    q.push({nextIndex, step + 1});
                }
            }
        }
        return 0;
    }

private:
    bool isOneCharDiff(const string &a, const string &b)
    {
        int diffCount = 0;
        for (int i = 0; i < a.size(); i++)
        {
            if (a[i] != b[i])
            {
                diffCount++;
                if (diffCount > 1)
                    return false;
            }
        }
        return diffCount == 1;
    }
};

// 使用*号简化建图过程：
// 处理 hot：
// 生成模式："*ot", "h*t", "ho*"。
// 在图里，"hot" 节点分别与 "*ot", "h*t", "ho*" 这三个通用模式节点建立边。

// 处理 dot：
// 生成模式："*ot", "d*t", "do*"。
// "dot" 节点与 "d*t", "do*" 建立边。
// 关键点来了： "dot" 节点与 "hot" 节点都生成了 "**ot**" 这个模式，所以它们都与 "**ot**" 这个通用模式节点相连。

// 只要两个单词只差一个字母，它们就一定会连接到同一个通用模式节点。
class Solution2
{
private:
    unordered_map<string, int> wordIndex; // 单词 -> pattern节点的index
    int index = 0;
    vector<vector<int>> edges; // 邻接表
public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        for (string &word : wordList)
        {
            addEdge(word); // 建立word与pattern的双向边
        }
        addEdge(beginWord); // beginWord可能不在wordList中，因此也要添加
        if (!wordIndex.count(endWord))
            return 0;

        vector<int> distance(index, -1);
        int beginIndex = wordIndex[beginWord];
        int endIndex = wordIndex[endWord];
        distance[beginIndex] = 0;
        queue<int> q;
        q.push(beginIndex);
        while (!q.empty())
        {
            int current = q.front();
            q.pop();
            if (current == endIndex)
                return distance[current] / 2 + 1; // word与pattern节点交替出现，因此除以2
            for (const auto &next : edges[current]) // 遍历邻接节点
            {
                if (distance[next] == -1) // 未访问
                {
                    distance[next] = distance[current] + 1;
                    q.push(next);
                }
            }
        }
        return 0;
    }

private:
    void addWord(const string &word)
    {
        if (!wordIndex.count(word))
        {
            wordIndex[word] = index++;
            edges.push_back({});
        }
    }

    void addEdge(string &word)
    {
        addWord(word);
        int wordId = wordIndex[word];
        for (int i = 0; i < word.size(); i++)
        {
            char originalChar = word[i];
            word[i] = '*';
            addWord(word);
            int patternId = wordIndex[word];
            edges[wordId].push_back(patternId);
            edges[patternId].push_back(wordId);
            word[i] = originalChar;
        }
    }
};

// 双向BFS：beginWord和endWord同时开始搜索，两者相遇时即找到最短路径
class Solution3
{
private:
    unordered_map<string, int> wordIndex; // 单词 -> pattern节点的index
    int index = 0;
    vector<vector<int>> edges; // 邻接表
public:
    int ladderLength(string beginWord, string endWord, vector<string> &wordList)
    {
        for (string &word : wordList)
        {
            addEdge(word); // 建立word与pattern的双向边
        }
        addEdge(beginWord); // beginWord可能不在wordList中，因此也要添加
        if (!wordIndex.count(endWord))
            return 0;

        vector<int> distanceBegin(index, -1);
        int beginIndex = wordIndex[beginWord];
        distanceBegin[beginIndex] = 0;
        queue<int> qBegin;
        qBegin.push(beginIndex);

        vector<int> distanceEnd(index, -1);
        int endIndex = wordIndex[endWord];
        distanceEnd[endIndex] = 0;
        queue<int> qEnd;
        qEnd.push(endIndex);

        while (!qBegin.empty() && !qEnd.empty())
        {
            int queBeginSize = qBegin.size();
            for (int i = 0; i < queBeginSize; i++)
            {
                int current = qBegin.front();
                qBegin.pop();
                if (distanceEnd[current] != -1) // 双向BFS相遇
                    return (distanceBegin[current] + distanceEnd[current]) / 2 + 1;
                for (const auto &next : edges[current]) // 遍历邻接节点
                {
                    if (distanceBegin[next] == -1) // 未访问
                    {
                        distanceBegin[next] = distanceBegin[current] + 1;
                        qBegin.push(next);
                    }
                }
            }

            int queEndSize = qEnd.size();
            for (int i = 0; i < queEndSize; i++)
            {
                int current = qEnd.front();
                qEnd.pop();
                if (distanceBegin[current] != -1) // 双向BFS相遇
                    return (distanceBegin[current] + distanceEnd[current]) / 2 + 1;
                for (const auto &next : edges[current]) // 遍历邻接节点
                {
                    if (distanceEnd[next] == -1) // 未访问
                    {
                        distanceEnd[next] = distanceEnd[current] + 1;
                        qEnd.push(next);
                    }
                }
            }
        }
        return 0;
    }

private:
    void addWord(const string &word)
    {
        if (!wordIndex.count(word))
        {
            wordIndex[word] = index++;
            edges.push_back({});
        }
    }

    void addEdge(string &word)
    {
        addWord(word);
        int wordId = wordIndex[word];
        for (int i = 0; i < word.size(); i++)
        {
            char originalChar = word[i];
            word[i] = '*';
            addWord(word);
            int patternId = wordIndex[word];
            edges[wordId].push_back(patternId);
            edges[patternId].push_back(wordId);
            word[i] = originalChar;
        }
    }
};