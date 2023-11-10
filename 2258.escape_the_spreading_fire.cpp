#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <array>

using std::vector, std::queue, std::array;

// 0: grass
// 1: fire   => 0
// 2: wall   => -1
// 第51组数据 TLE 了，不想写了，优化不了一点
int maximum_minutes(vector<vector<int>>& g)
{
    int m = g.size(), n = g[0].size();
    vector<array<int, 2>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    auto adj = [&g, &dirs, m, n](int x, int y) -> vector<array<int, 2>> {
        vector<array<int, 2>> res;
        for (const auto [dx, dy] : dirs) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
                continue;
            }
            res.push_back({nx, ny});
        }
        return res;
    };

    auto spread = [&adj, &g, m, n](int x, int y) {
        queue<array<int, 2>> q;
        q.push({x, y});
        vector<vector<int>> vis(m, vector<int>(n, 0));

        vis[x][y] = 1;
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (const auto [nx, ny] : adj(x, y)) {
                if (g[nx][ny] != -1 && vis[nx][ny] != 1) {
                    g[nx][ny] = std::min(g[nx][ny], g[x][y] + 1);
                    q.push({nx, ny});
                    vis[nx][ny] = 1;
                }
            }
        }
    };

    // queue<array<int, 2>> q;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j] == 1) {
                g[i][j] = 0;
            } else if (g[i][j] == 2) {
                g[i][j] = -1;
            } else if (g[i][j] == 0) {
                g[i][j] = 1000000;
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j] == 0) {
                spread(i, j);
            }
        }
    }

    auto bfs = [&adj, &g, m, n](int t) -> bool {
        queue<array<int, 2>> q;
        vector<vector<int>> vis(m, vector<int>(n, 0));

        q.push({0, 0});
        vis[0][0] = 1;
        while (!q.empty()) {
            ++t;
            int k = q.size();
            for (int i = 0; i < k; ++i) {
                auto [x, y] = q.front();
                q.pop();

                for (const auto [nx, ny] : adj(x, y)) {
                    // not fire and wall
                    // if (vis[nx][ny] != 1 && g[nx][ny] != 0 && g[nx][ny] != -1) {
                    // 里面还会判断 g[nx][ny] >= t，因为 t 一定是大于零的
                    // 故而外面不需要判断了
                    if (vis[nx][ny] != 1) {
                        // 最后一个格子可以直接进去，难崩
                        if (nx == m - 1 && ny == n - 1 && g[nx][ny] >= t) {
                            return true;
                        } else if (g[nx][ny] > t) {
                            q.push({nx, ny});
                            vis[nx][ny] = 1;
                        }
                    }
                }
            }
        }
        return false;
    };

    bool a = bfs(0);


    // 既然每个点能停留到什么时候都知道了
    // 那么就可以枚举所有可能的 t 了啊
    // 还可以用二分加快
    // 从 (0,0) bfs 到 (m-1,n-1)
    int N = m * n + 10;
    int l = 0, r = N;
    while (l < r) {
        int m = (l + r + 1) >> 1;
        if (bfs(m)) l = m;
        else r = m - 1;
    }

    if (l == 0) {
        return bfs(0) ? 0 : -1;
    } else if (l == N) {
        return 1e9l;
    } else {
        return l;
    }
}

int main () {
#ifdef LOCAL
    freopen("2258.in", "r", stdin);
#endif
    int m = 0, n = 0;
    while (std::cin >> m >> n) {
        vector<vector<int>> g(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> g[i][j];
            }
        }
        std::cout << maximum_minutes(g) << std::endl;
    }

    return 0;
}
