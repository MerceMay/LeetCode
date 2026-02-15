#include <vector>
#include <string>
#include <set>
using namespace std;
// 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

// 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

// 示例 1：

// 输入：digits = "23"
// 输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
// 示例 2：

// 输入：digits = ""
// 输出：[]
// 示例 3：

// 输入：digits = "2"
// 输出：["a","b","c"]

// 提示：

// 0 <= digits.length <= 4
// digits[i] 是范围 ['2', '9'] 的一个数字。
class Solution
{
private:
    vector<string> mapping = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

public:
    vector<string> letterCombinations(string digits)
    {
        vector<string> result;
        if (digits.empty())
            return result;
        string path;
        backtrack(digits, 0, path, result);
        return result;
    }

private:
    void backtrack(string &digits, int index, string &path, vector<string> &result)
    {
        if (index == digits.size())
        {
            result.push_back(path);
            return;
        }
        char digit = digits[index];
        const string &letters = mapping[digit - '2'];
        for (char c : letters)
        {
            path.push_back(c);
            backtrack(digits, index + 1, path, result);
            path.pop_back();
        }
    }
};