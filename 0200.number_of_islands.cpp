#include <array>
#include <iostream>
#include <vector>
#include <queue>

using std::vector, std::queue, std::array;

// dfs 都过了，bfs TLE
int num_is_lands(vector<vector<int>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();

    vector<std::array<int, 2>> dirs = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},
    };

    auto adj = [&dirs, m, n](int x, int y) -> vector<std::array<int, 2>> {
        vector<std::array<int, 2>> res;
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

    auto bfs = [&adj, &grid](int x, int y) -> void {
        queue<std::array<int, 2>> q;

        q.push({x, y});
        while (!q.empty()) {
            const auto [x, y] = q.front();
            q.pop();
            grid[x][y] = 0;

            for (const auto [nx, ny] : adj(x, y)) {
                if (grid[nx][ny] == 1) {
                    q.push({nx, ny});
                }
            }
        }
    };

    int res = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1) {
                ++res;
                bfs(i, j);
            }
        }
    }

    return res;
}

// MD，题目给的数据是 char 数组啊
// WA 半天没看出来为啥
int _num_is_lands(vector<vector<int>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();

    vector<std::array<int, 2>> dirs = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},
    };

    auto adj = [&dirs, m, n](int x, int y) -> vector<std::array<int, 2>> {
        vector<std::array<int, 2>> res;

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


    // 把相邻的都变为 0
    auto dfs = [&adj, &grid](auto&& self, int x, int y) {
        if (grid[x][y] == 0) return ;

        grid[x][y] = 0;
        for (const auto [nx, ny] : adj(x, y)) {
            self(self, nx, ny);
        }
    };

    int res = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 1) {
                ++res;
                dfs(dfs, i, j);
            }
        }
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0200.in", "r", stdin);
#endif
    int m = 0, n = 0;
    while (std::cin >> m >> n) {
        vector<vector<int>> grid(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> grid[i][j];
            }
        }
        std::cout << num_is_lands(grid) << std::endl;
    }

    return 0;
}
