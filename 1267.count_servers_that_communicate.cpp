#include <iostream>
#include <vector>
#include <utility>
#include <queue>

using std::vector, std::tuple, std::queue;

int count_server(vector<vector<int>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();

    vector<int> row(m, 0);
    vector<int> col(n, 0);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1) {
                row[i]++;
                col[j]++;
            }
        }
    }

    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cnt += grid[i][j] & (row[i] > 1 | col[j] > 1);
        }
    }

    return cnt;
}

// 没读题，面向杨例编程，WA了
int _count_server(vector<vector<int>>& grid)
{
    int cnt = 0;
    int m = grid.size();
    int n = grid[0].size();
    // vector<vector<bool>> vis(m, vector<bool>(n, false));
    // 不需要 vis，走过的直接 grid[i][j] = -1 即可

    vector<tuple<int, int>> dirs = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
    };

    auto adj = [&dirs, &grid, &m, &n](int x, int y) -> vector<tuple<int, int>> {
        vector<tuple<int, int>> res;

        for (auto& dir : dirs) {
            auto [dx, dy] = dir;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                res.push_back({nx, ny});
            }
        }

        return res;
    };

    auto next = [&grid, &m, &n]() -> tuple<int, int> {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    };

    while (next() != tuple<int, int>{-1, -1}) {
        auto [x, y] = next();

        queue<tuple<int, int>> q;
        q.push({x, y});
        int cnt_ = 0;

        while (!q.empty()) {
            auto& [x, y] = q.front();
            q.pop();
            ++cnt_;

            for (auto& [nx, ny] : adj(x, y)) {
                if (grid[nx][ny] == 1) {
                    q.push({nx, ny});
                }
            }
            grid[x][y] = -1;
        }

        if (cnt_ > 1) {
            cnt += cnt_;
        }
    }


    // 容易想到，每次选定一个点 BFS
    // 结束后再选择下一个没被访问过的作为起点 BFS
    // 这写得也乱七八糟，逻辑混乱
    // queue<tuple<int, int>> q;
    // q.push(next());
    // while (!q.empty()) {
    //     auto [x, y] = q.front();
    //     q.pop();
    //     if (x == -1) continue;
    //
    //     int c = 1;
    //     grid[x][y] = -1;
    //
    //     if (c > 1) {
    //         cnt += c;
    //     }
    //
    //     auto [nx, ny] = next();
    //     if (nx != -1) {
    //         q.push({nx, ny});
    //     }
    // }


    // 对每个点都做一次 BFS？
    // 这写得啥玩意儿啊？一点都不优雅
    // queue<tuple<int, int>> q;
    // for (int i = 0; i < m; ++i) {
    //     for (int j = 0; j < n; ++j) {
    //         if (!vis[i][j]) {
    //             q.push({i, j});
    //             int c = 0;
    //             while (!q.empty()) {
    //                 auto [x, y] = q.front();
    //                 q.pop();
    //                 vis[x][y] = true;
    //                 ++c;
    //
    //                 for (auto& [nx, ny] : adj(x, y)) {
    //                     if(!vis[nx][ny]) {
    //                         q.push({nx, ny});
    //                     }
    //                 }
    //             }
    //             if (c > 1) cnt += c;
    //         }
    //     }
    // }

    return cnt;
}

int main()
{
#ifdef LOCAL
    freopen("1267.in", "r", stdin);
#endif
    int m = 0, n = 0;
    while (std::cin >> m >> n) {
        vector<vector<int>> grid(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> grid[i][j];
            }
        }
        std::cout << count_server(grid) << std::endl;
    }
    return 0;
}

