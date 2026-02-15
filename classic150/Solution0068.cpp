#include <vector>
#include <string>
using namespace std;
// 给定一个单词数组 words 和一个长度 maxWidth ，重新排版单词，使其成为每行恰好有 maxWidth 个字符，且左右两端对齐的文本。

// 你应该使用 “贪心算法” 来放置给定的单词；也就是说，尽可能多地往每行中放置单词。必要时可用空格 ' ' 填充，使得每行恰好有 maxWidth 个字符。

// 要求尽可能均匀分配单词间的空格数量。如果某一行单词间的空格不能均匀分配，则左侧放置的空格数要多于右侧的空格数。

// 文本的最后一行应为左对齐，且单词之间不插入额外的空格。

// 注意:

// 单词是指由非空格字符组成的字符序列。
// 每个单词的长度大于 0，小于等于 maxWidth。
// 输入单词数组 words 至少包含一个单词。

// 示例 1:

// 输入: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
// 输出:
// [
//    "This    is    an",
//    "example  of text",
//    "justification.  "
// ]
// 示例 2:

// 输入:words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
// 输出:
// [
//   "What   must   be",
//   "acknowledgment  ",
//   "shall be        "
// ]
// 解释: 注意最后一行的格式应为 "shall be    " 而不是 "shall     be",
//      因为最后一行应为左对齐，而不是左右两端对齐。
//      第二行同样为左对齐，这是因为这行只包含一个单词。
// 示例 3:

// 输入:words = ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"]，maxWidth = 20
// 输出:
// [
//   "Science  is  what we",
//   "understand      well",
//   "enough to explain to",
//   "a  computer.  Art is",
//   "everything  else  we",
//   "do                  "
// ]

// 提示:

// 1 <= words.length <= 300
// 1 <= words[i].length <= 20
// words[i] 由小写英文字母和符号组成
// 1 <= maxWidth <= 100
// words[i].length <= maxWidth
class Solution
{
public:
    vector<string> fullJustify(vector<string> &words, int maxWidth)
    {
        vector<string> result;
        int n = words.size();
        int i = 0;
        while (i < n)
        {
            int j = i;
            int lineLength = 0;
            while (j < n && lineLength + words[j].size() + (j - i) <= maxWidth)
                lineLength += words[j++].size();
            addLine(words, i, j, maxWidth, result, lineLength);
            i = j;
        }
        return result;
    }

private:
    void addLine(vector<string> &words, int start, int end, int maxWidth, vector<string> &result, int lineLength)
    {
        int totalChars = lineLength;
        int numSpaces = maxWidth - totalChars;
        int numWords = end - start;

        // 单个字符或者最后一行
        if (numWords == 1 || end == words.size())
        {
            string line = words[start];
            for (int i = start + 1; i < end; i++)
                line += " " + words[i];
            line += string(maxWidth - line.size(), ' ');
            result.push_back(line);
            return;
        }

        // 分配空格
        int spaceBetweenWords = numSpaces / (numWords - 1);
        int extraSpaces = numSpaces % (numWords - 1);

        string line = words[start];
        for (int i = start + 1; i < end; i++)
        {
            int spaces = spaceBetweenWords + (extraSpaces-- > 0 ? 1 : 0);
            line += string(spaces, ' ') + words[i];
        }
        result.push_back(line);
    }
};