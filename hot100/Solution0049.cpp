#include <iostream>
#include <unordered_map>
#include <vector>
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
class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        unordered_map<string, vector<string>> anagrams;
        for (const auto &str : strs)
        {
            string key = str;
            sort(key.begin(), key.end());
            anagrams[key].push_back(str);
        }
        vector<vector<string>> result;
        for (const auto &pair : anagrams)
        {
            result.push_back(pair.second);
        }
        return result;
    }
};

class Solution2
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        auto arrayHash = [fn = hash<int>{}](const array<int, 26> arr) -> size_t
        {
            return accumulate(arr.begin(), arr.end(), 0u, [&](size_t acc, int num)
                              { return (acc << 1) ^ fn(num); });
        };
        unordered_map<array<int, 26>, vector<string>, decltype(arrayHash)> mp(0, arrayHash);
        for (string &str : strs)
        {
            array<int, 26> counts;
            int length = str.length();
            for (int i = 0; i < length; ++i)
            {
                counts[str[i] - 'a']++;
            }
            mp[counts].push_back(str);
        }
        vector<vector<string>> result;
        for (auto it = mp.begin(); it != mp.end(); ++it)
        {
            result.push_back(it->second);
        }
        return result;
    }
};