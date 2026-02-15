#include <string>
#include <vector>
#include <algorithm>
using namespace std;
// 给你一个字符串 s 。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。例如，字符串 "ababcc" 能够被分为 ["abab", "cc"]，但类似 ["aba", "bcc"] 或 ["ab", "ab", "cc"] 的划分是非法的。

// 注意，划分结果需要满足：将所有划分结果按顺序连接，得到的字符串仍然是 s 。

// 返回一个表示每个字符串片段的长度的列表。

// 示例 1：
// 输入：s = "ababcbacadefegdehijhklij"
// 输出：[9,7,8]
// 解释：
// 划分结果为 "ababcbaca"、"defegde"、"hijhklij" 。
// 每个字母最多出现在一个片段中。
// 像 "ababcbacadefegde", "hijhklij" 这样的划分是错误的，因为划分的片段数较少。
// 示例 2：

// 输入：s = "eccbbbbdec"
// 输出：[10]

// 提示：

// 1 <= s.length <= 500
// s 仅由小写英文字母组成

// 找到每个字母最后出现的位置
// 然后从开始遍历数组，假设遍历到i，使用end标记包含s[i]的片段的结尾位置
// 如果end == s[i]，说明这个一个片段，可以结尾了。
class Solution
{
public:
    vector<int> partitionLabels(string s)
    {
        vector<int> lastIndex(26, -1);
        for (int i = 0; i < s.size(); i++)
            lastIndex[s[i] - 'a'] = i;
        vector<int> result;
        int start = 0, end = 0;
        for (int i = 0; i < s.size(); i++)
        {
            end = max(end, lastIndex[s[i] - 'a']);
            if (i == end) // 到达了当前片段的结尾
            {
                result.push_back(end - start + 1);
                start = i + 1;
            }
        }
        return result;
    }
};

// 记录每个字幕第一次出现和最后一次出现的位置
class Solution2
{
    public:
    vector<int> partitionLabels(string s)
    {
        vector<pair<int, int>> charRange(26, {-1, -1});
        for (int i = 0; i < s.size(); i++)
        {
            if (charRange[s[i] - 'a'].first == -1)
                charRange[s[i] - 'a'].first = i;
            charRange[s[i] - 'a'].second = i;
        }
        sort(charRange.begin(), charRange.end());
        // 合并重叠区间
        vector<pair<int, int>> merged;
        for (const auto& range : charRange)
        {
            if (range.first == -1) continue; // 跳过未出现的字符
            if (merged.empty() || merged.back().second < range.first)
                merged.push_back(range);
            else
                merged.back().second = max(merged.back().second, range.second);
        }
        // 计算每个合并区间的长度
        vector<int> result;
        for (const auto& range : merged)
            result.push_back(range.second - range.first + 1);
        return result;
    }
};