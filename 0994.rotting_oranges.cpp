#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <vector>

using std::vector, std::array, std::queue;

int oranges_rotting(vector<vector<int>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();

    vector<array<int, 2>> dirs = {
        {1,0}, {-1,0}, {0,1}, {0,-1},
    };

    auto adj = [&grid, &dirs, m, n](int x, int y) -> vector<array<int, 2>> {
        vector<array<int, 2>> adjs;
        for (const auto& [dx, dy] : dirs) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
            adjs.push_back({nx, ny});
        }
        return adjs;
    };

    int res = 0;
    int cnt = 0;
    queue<array<int, 2>> q;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] != 0) cnt++;
            if (grid[i][j] == 2) res++;
            if (grid[j][j] == 2) q.push({i, j});
        }
    }

    if (res == 0 && cnt != 0) return -1;
    else if (res == cnt) return 0;

    // bfs 开启
    int time = -1;
    while (!q.empty()) {
        int t = q.size();
        time++;
        for (int i = 0; i < t; ++i) {
            const auto [x, y] = q.front();
            q.pop();
            for (const auto& [nx, ny] : adj(x, y)) {
                if (grid[nx][ny] == 1) {
                    q.push({nx, ny});
                    grid[nx][ny] = 0;
                    res++;
                }
            }
        }
    }

    return res == cnt ? time : -1;
}

// 不行，不能这么一个个的 bfs
// 应该同时扔进去 bfs
// 烂橘子可不会等你烂完了它再继续烂
int _oranges_rotting(vector<vector<int>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();

    vector<array<int, 2>> dirs = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},
    };

    auto adj = [&grid, &dirs, m, n](int x, int y) -> vector<array<int, 2>> {
        vector<array<int, 2>> res;
        for (const auto& [dx, dy] : dirs) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
            res.push_back({nx, ny});
        }
        return res;
    };

    int res = 0;
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] != 0) cnt++;
            if (grid[i][j] == 2) res++;
        }
    }

    // [[0]]
    // 这个特判显然有失偏颇，当时读差题了捏
    if (cnt == 0) return 0;

    auto bfs = [&grid, &adj, &res](int u, int v) -> int {
        int time = -1;

        queue<array<int, 2>> q;
        q.push({u, v});
        while (!q.empty()) {
            int n = q.size();
            time++;
            for (int i = 0; i < n; ++i) {
                const auto [x, y] = q.front();
                q.pop();
                for (const auto& [nx, ny] : adj(x, y)) {
                    if (grid[nx][ny] == 1) {
                        q.push({nx, ny});
                        grid[nx][ny] = 0;
                        res++;
                    }
                }
            }
        }

        return time;
    };

    int time = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 2) {
                time = std::max(time, bfs(i, j));
            }
        }
    }

    return res == cnt ? time : -1;
}

int main () {
#ifdef LOCAL
    freopen("0994.in", "r", stdin);
#endif
    int m = 0, n = 0;
    while (std::cin >> m >> n) {
        vector<vector<int>> nums(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> nums[i][j];
            }
        }
        std::cout << oranges_rotting(nums) << std::endl;
    }

    return 0;
}
