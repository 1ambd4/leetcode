#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <utility>
#include <deque>

#include "leetcode.h"

using std::vector, std::pair, std::deque, std::queue;


vector<vector<int>> queens_attack_the_king(vector<vector<int>>& queens, vector<int>& king)
{
    vector<vector<int>> res;
    vector<pair<int, int>> dirs {
        {0,1}, {1,1}, {1,0}, {1,-1},
        {0,-1}, {-1,-1}, {-1,0}, {-1,1},
    };
    vector<vector<char>> m(8, std::vector<char>(8, ' '));
    std::for_each(queens.begin(), queens.end(), [&m](const vector<int>& queen) {
            m[queen[0]][queen[1]] = 'q';
        });

    for (const auto& [dx, dy] : dirs) {
        int x = king[0] + dx;
        int y = king[1] + dy;

        while (0 <= x && x < 8 && 0 <= y && y < 8) {
            if (m[x][y] == 'q') {
                res.push_back({x, y});
                break;
            }
            x += dx;
            y += dy;
        }
    }

    return res;
}


// 完全想错哩，我这成了全图遍历了
vector<vector<int>> _queens_attack_the_king(vector<vector<int>>& queens, vector<int>& king)
{
    vector<vector<int>> res;

    vector<vector<char>> m(8, std::vector<char>(8, ' '));
    int x = king[0], y = king[1];
    m[x][y] = 'z';

    std::for_each(queens.begin(), queens.end(), [&m](const vector<int>& queen) {
            m[queen[0]][queen[1]] = 'q';
        });

    deque<pair<int, int>> _dirs = {
        {0,1}, {1,1}, {1,0}, {1,-1},
        {0,-1}, {-1,-1}, {-1,0}, {-1,1},
    };
    queue<pair<int, int>> dirs(_dirs);

    queue<pair<int, int>> q;
    q.push({king[0], king[1]});
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; ++i) {
            auto [x, y] = q.front();
            q.pop();

            int t = dirs.size();
            for (int j = 0; j < t; ++j) {
                auto [dx, dy] = dirs.front();
                dirs.pop();
                int nx = x + dx;
                int ny = y + dy;

                if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8) continue;
                if (m[nx][ny] == 'z') {
                    dirs.push({dx, dy});
                    continue;
                }

                if (m[nx][ny] == 'q') {
                    res.push_back({nx, ny});
                    m[nx][ny] = 'z';
                    continue;
                } else if (m[nx][ny] == 'z') {
                    dirs.push({dx, dy});
                    continue;
                } else {
                    dirs.push({dx,dy});
                    q.push({nx,ny});
                }
            }
        }
    }

    return res;
}

int main()
{
#ifdef LOCAL
    freopen("1222.in", "r", stdin);
#endif
    int n = 0;
    int x = 0, y = 0;
    while (std::cin >> n) {
        std::vector<int> king;
        std::cin >> x >> y;
        king.push_back(x);
        king.push_back(y);

        std::vector<std::vector<int>> queens(n, std::vector<int>());
        for (int i = 0; i < n; ++i) {
            std::cin >> x >> y;
            queens[i].push_back(x);
            queens[i].push_back(y);
        }

        std::vector<std::vector<int>> res =
            queens_attack_the_king(queens, king);
        std::cout << res << std::endl;
    }

    return 0;
}
