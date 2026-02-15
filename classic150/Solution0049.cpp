#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <numeric>
#include <array>
using namespace std;
// 给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。

// 示例 1:

// 输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]

// 输出: [["bat"],["nat","tan"],["ate","eat","tea"]]

// 解释：

// 在 strs 中没有字符串可以通过重新排列来形成 "bat"。
// 字符串 "nat" 和 "tan" 是字母异位词，因为它们可以重新排列以形成彼此。
// 字符串 "ate" ，"eat" 和 "tea" 是字母异位词，因为它们可以重新排列以形成彼此。
// 示例 2:

// 输入: strs = [""]

// 输出: [[""]]

// 示例 3:

// 输入: strs = ["a"]

// 输出: [["a"]]

// 提示：

// 1 <= strs.length <= 104
// 0 <= strs[i].length <= 100
// strs[i] 仅包含小写字母
class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        vector<vector<string>> result;
        unordered_map<string, vector<string>> anagramMap;
        for (const string &s : strs)
        {
            string key = s;
            sort(key.begin(), key.end());
            anagramMap[key].push_back(s);
        }
        for (auto it = anagramMap.begin(); it != anagramMap.end(); ++it)
        {
            result.push_back(it->second);
        }
        return result;
    }
};

class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        struct arrayHash
        {
            size_t operator()(const array<int, 26> &arr) const
            {
                return accumulate(arr.begin(), arr.end(), 0u, [&](size_t acc, int num)
                                  { return (acc << 1) ^ hash<int>{}(num); });
            }
        };
        unordered_map<array<int, 26>, vector<string>, arrayHash> anagramMap;
        for (const string &s : strs)
        {
            array<int, 26> charCount = {};
            for (char c : s)
            {
                charCount[c - 'a']++;
            }
            anagramMap[charCount].push_back(s);
        }
        vector<vector<string>> result;
        for (auto it = anagramMap.begin(); it != anagramMap.end(); ++it)
        {
            result.push_back(it->second);
        }
        return result;
    }
};