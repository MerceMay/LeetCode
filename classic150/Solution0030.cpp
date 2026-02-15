#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
// 给定一个字符串 s 和一个字符串数组 words。 words 中所有字符串 长度相同。

//  s 中的 串联子串 是指一个包含  words 中所有字符串以任意顺序排列连接起来的子串。

// 例如，如果 words = ["ab","cd","ef"]， 那么 "abcdef"， "abefcd"，"cdabef"， "cdefab"，"efabcd"， 和 "efcdab" 都是串联子串。 "acdbef" 不是串联子串，因为他不是任何 words 排列的连接。
// 返回所有串联子串在 s 中的开始索引。你可以以 任意顺序 返回答案。

// 示例 1：

// 输入：s = "barfoothefoobarman", words = ["foo","bar"]
// 输出：[0,9]
// 解释：因为 words.length == 2 同时 words[i].length == 3，连接的子字符串的长度必须为 6。
// 子串 "barfoo" 开始位置是 0。它是 words 中以 ["bar","foo"] 顺序排列的连接。
// 子串 "foobar" 开始位置是 9。它是 words 中以 ["foo","bar"] 顺序排列的连接。
// 输出顺序无关紧要。返回 [9,0] 也是可以的。
// 示例 2：

// 输入：s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
// 输出：[]
// 解释：因为 words.length == 4 并且 words[i].length == 4，所以串联子串的长度必须为 16。
// s 中没有子串长度为 16 并且等于 words 的任何顺序排列的连接。
// 所以我们返回一个空数组。
// 示例 3：

// 输入：s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
// 输出：[6,9,12]
// 解释：因为 words.length == 3 并且 words[i].length == 3，所以串联子串的长度必须为 9。
// 子串 "foobarthe" 开始位置是 6。它是 words 中以 ["foo","bar","the"] 顺序排列的连接。
// 子串 "barthefoo" 开始位置是 9。它是 words 中以 ["bar","the","foo"] 顺序排列的连接。
// 子串 "thefoobar" 开始位置是 12。它是 words 中以 ["the","foo","bar"] 顺序排列的连接。

// 提示：

// 1 <= s.length <= 104
// 1 <= words.length <= 5000
// 1 <= words[i].length <= 30
// words[i] 和 s 由小写英文字母组成
class Solution
{
public:
    vector<int> findSubstring(string s, vector<string> &words)
    {
        int wordSize = words[0].size();
        int wordNum = words.size();
        int totalLength = wordSize * wordNum;

        vector<int> result;
        /*
            滑动思想：滑动窗口大小固定为wordSize*wordNum，每一次滑动去掉一个前面的单词
            增加一个后面的单词，并判断是否满足题意，满足则将起始下标加入答案中
        */
        /*
            i代表滑动的起始位置，i只需要从0~wordSize-1之间开始即可，因为i如果从wordSize开始，
            其实就相当于从0开始，然后滑动了一次的结果，如果从wordSize+1开始，相当于从1开始滑动了一次
            假如又从2*wordSize开始，相当于从0滑动了两次的结果，以此类推，所以会有重复的判断，因此只需要从0-wordSize-1开始
        */
        for (int i = 0; i < wordSize && i <= (int)s.size() - totalLength; i++)
        {
            // 滑动窗口边界
            int left = i;
            int right = i + totalLength;
            unordered_map<string, int> wordCount; // 记录窗口中和words中的关系
            for (int j = left; j < right; j += wordSize)
                wordCount[s.substr(j, wordSize)]++;
            for (const auto &word : words)
            {
                wordCount[word]--;
                if (wordCount[word] == 0)
                    wordCount.erase(word);
            }
            if (wordCount.empty())
                result.push_back(left);
            // 滑动窗口
            while (right + wordSize <= s.size())
            {
                const string &deleteWord = s.substr(left, wordSize);
                const string &addWord = s.substr(right, wordSize);
                if (--wordCount[deleteWord] == 0)
                    wordCount.erase(deleteWord);
                if (++wordCount[addWord] == 0)
                    wordCount.erase(addWord);

                left += wordSize;
                right += wordSize;
                if (wordCount.empty())
                    result.push_back(left);
            }
        }
        return result;
    }
};