#include <vector>
#include <unordered_map>
#include <functional>
#include <numeric>
#include <unordered_set>
using namespace std;
// 给你一个数组 points ，其中 points[i] = [xi, yi] 表示 X-Y 平面上的一个点。求最多有多少个点在同一条直线上。

// 方法一：使用全局法，统计每一条线对应哪几个点
// 使用A*x + B*y + C = 0来表示一条直线
class Solution
{
private:
    struct Line
    {
        int A, B, C;
        Line(int a, int b, int c) : A(a), B(b), C(c) {}
        bool operator==(const Line &other) const
        {
            return A == other.A && B == other.B && C == other.C;
        }
    };
    struct LineHasher
    {
        size_t operator()(const Line &line) const
        {
            return hash<int>()(line.A) ^ hash<int>()(line.B << 1) ^ hash<int>()(line.C << 2);
        }
    };

public:
    int maxPoints(vector<vector<int>> &points)
    {
        int n = points.size();
        if (n <= 2)
            return n;
        unordered_map<Line, unordered_set<int>, LineHasher> line_map;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];

                int A = y2 - y1;
                int B = x1 - x2;
                int C = x2 * y1 - x1 * y2;
                int g = gcd(gcd(abs(A), abs(B)), abs(C));
                if (g != 0)
                {
                    A /= g;
                    B /= g;
                    C /= g;
                }

                if (A < 0 || (A == 0 && B < 0))
                {
                    A = -A;
                    B = -B;
                    C = -C;
                }

                Line line(A, B, C);
                line_map[line].insert(i); // 这里插入的不是点，而是下标，因此，使用unordered_set即可
                line_map[line].insert(j);
            }
        }
        int result = 0;
        for (auto &[key, value] : line_map)
        {
            result = max(result, static_cast<int>(value.size()));
        }
        return result;
    }
};

// 方法二：使用局部法，统计每个点与其他点的连线
class Solution2
{
public:
    int maxPoints(vector<vector<int>> &points)
    {
        int n = points.size();
        if (n <= 2)
            return n;
        int result = 0;

        for (int i = 0; i < n; i++)
        {
            unordered_map<long long, int> slope_count;
            int duplicates = 1; // 重合点数量
            int vertical = 0;   // 垂直线数量
            int local_max = 0;

            for (int j = i + 1; j < n; j++)
            {
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];

                if (dx == 0 && dy == 0)
                {
                    // 重合点
                    duplicates++;
                }
                else if (dx == 0)
                {
                    // 垂直线
                    vertical++;
                    local_max = max(local_max, vertical);
                }
                else
                {
                    int g = gcd(dx, dy);
                    dx /= g;
                    dy /= g;
                    // 保证唯一性（比如 dx<0 时翻转符号）
                    if (dx < 0)
                    {
                        dx = -dx;
                        dy = -dy;
                    }
                    // 用 pair(dx,dy) 编码为 long long，避免 pair 作为 key 的麻烦
                    long long key = ((long long)dx << 32) ^ (long long)dy;
                    slope_count[key]++;
                    local_max = max(local_max, slope_count[key]);
                }
            }
            result = max(result, local_max + duplicates);
        }
        return result;
    }
};
