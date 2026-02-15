#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;
// 基因序列可以表示为一条由 8 个字符组成的字符串，其中每个字符都是 'A'、'C'、'G' 和 'T' 之一。

// 假设我们需要调查从基因序列 start 变为 end 所发生的基因变化。一次基因变化就意味着这个基因序列中的一个字符发生了变化。

// 例如，"AACCGGTT" --> "AACCGGTA" 就是一次基因变化。
// 另有一个基因库 bank 记录了所有有效的基因变化，只有基因库中的基因才是有效的基因序列。（变化后的基因必须位于基因库 bank 中）

// 给你两个基因序列 start 和 end ，以及一个基因库 bank ，请你找出并返回能够使 start 变化为 end 所需的最少变化次数。如果无法完成此基因变化，返回 -1 。

// 注意：起始基因序列 start 默认是有效的，但是它并不一定会出现在基因库中。

// 示例 1：

// 输入：start = "AACCGGTT", end = "AACCGGTA", bank = ["AACCGGTA"]
// 输出：1
// 示例 2：

// 输入：start = "AACCGGTT", end = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
// 输出：2
// 示例 3：

// 输入：start = "AAAAACCC", end = "AACCCCCC", bank = ["AAAACCCC","AAACCCCC","AACCCCCC"]
// 输出：3

// 提示：

// start.length == 8
// end.length == 8
// 0 <= bank.length <= 10
// bank[i].length == 8
// start、end 和 bank[i] 仅由字符 ['A', 'C', 'G', 'T'] 组成
// startGene -> endGene 相当于在bank图中找出最短路径
class Solution
{
public:
    int minMutation(string startGene, string endGene, vector<string> &bank)
    {
        unordered_set<string> bankSet(bank.begin(), bank.end());
        if (!bankSet.count(endGene))
            return -1;
        queue<pair<string, int>> q; // {gene,step}
        q.push({startGene, 0});
        unordered_set<string> visited;
        visited.insert(startGene);
        vector<char> geneChars = {'A', 'C', 'G', 'T'};
        while (!q.empty())
        {
            auto [gene, step] = q.front();
            q.pop();
            if (gene == endGene)
                return step;
            for (int i = 0; i < gene.size(); i++)
            {
                char oldChar = gene[i];
                for (const auto &c : geneChars)
                {
                    if (c == oldChar)
                        continue;
                    gene[i] = c;
                    if (bankSet.count(gene) && !visited.count(gene))
                    {
                        visited.insert(gene);
                        q.push({gene, step + 1});
                    }
                    gene[i] = oldChar;
                }
            }
        }
        return -1;
    }
};

// 使用邻接表：
// bank相当于图的节点，当两个节点之间只有一个字符不同，则这节点之间有边相连
class Solution2
{
public:
    int minMutation(string startGene, string endGene, vector<string> &bank)
    {
        int n = bank.size();
        vector<vector<int>> adjacencyList(n);
        int endGeneIndex = -1;
        // 构建邻接表
        for (int i = 0; i < n; i++)
        {
            if (bank[i] == endGene)
                endGeneIndex = i;
            for (int j = i + 1; j < n; j++)
            {
                if (isOneCharDiff(bank[i], bank[j]))
                {
                    adjacencyList[i].push_back(j);
                    adjacencyList[j].push_back(i);
                }
            }
        }

        if (endGeneIndex == -1)
            return -1;

        queue<pair<int, int>> q; // {index,step}
        vector<bool> visited(n);
        for (int i = 0; i < n; i++)
        {
            if (isOneCharDiff(startGene, bank[i]))
            {
                q.push({i, 1});
                visited[i] = true;
            }
        }
        while (!q.empty())
        {
            auto [index, step] = q.front();
            q.pop();
            if (index == endGeneIndex)
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
        return -1;
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
