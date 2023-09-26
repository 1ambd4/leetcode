#include <iostream>
#include <vector>
#include <utility>

#include "leetcode.h"

using std::vector, std::pair;

int unique_paths_with_obstacles(vector<vector<int>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();

    if (grid[m-1][n-1] == 1) return 0;

    vector<int> dp(n, 0);
    for (int i = 0, c = 1; i < n; ++i) {
        if (grid[0][i] == 1) c = 0;
        dp[i] = c;
    }

    for (int i = 1; i < m; ++i) {
        if (grid[i][0] == 1) dp[0] = 0;
        for (int j = 1; j < n; ++j) {
            if (grid[i][j] == 1) {
                dp[j] = 0;
            } else {
                dp[j] += dp[j-1];
            }
        }
    }


    return dp[n-1];
}

int _unique_paths_with_obstacles(vector<vector<int>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();

    if (grid[m-1][n-1] == 1) return 0;

    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0, c = 1; i < m; ++i) {
        if (grid[i][0] == 1) c = 0;
        dp[i][0] = c;
    }
    for (int i = 0, c = 1; i < n; ++i) {
        if (grid[0][i] == 1) c = 0;
        dp[0][i] = c;
    }

    for (int i = 1; i < m; ++i) {
        for (int j  = 1; j < n; ++j) {
            if (grid[i][j] == 1) {
                dp[i][j] = 0;
            } else {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
    }

    return dp[m-1][n-1];
}

// TLE 哩
int __unique_paths_with_obstacles(vector<vector<int>>& grid)
{
    int cnt = 0;

    int m = grid.size();
    int n = grid[0].size();

    if (grid[m-1][n-1] == 1) return 0;

    vector<pair<int, int>> dirs = {
        {1, 0}, {0, 1},
    };

    auto adj = [&dirs, m, n](int x, int y) -> vector<pair<int, int>> {
        vector<pair<int, int>> res;

        for (const auto& [dx, dy] : dirs) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
            res.push_back({nx, ny});
        }

        return res;
    };

    vector<vector<bool>> vis(m, vector<bool>(n, false));

    auto dfs = [&cnt, &adj, &grid, &vis, m, n](auto&& self, int x, int y) -> void {
        if (x == m - 1 && y == n - 1) {
            ++cnt;
            return ;
        }

        if (vis[x][y] || grid[x][y] == 1) return ;

        // vis[x][y] = true;

        vis[x][y] = true;
        for (const auto& [nx, ny] : adj(x, y)) {
            self(self, nx, ny);
        }
        vis[x][y] = false;
    };

    dfs(dfs, 0, 0);

    return cnt;
}

int main()
{
#ifdef LOCAL
    freopen("0063.in", "r", stdin);
#endif
    int m = 0, n = 0;
    while (std::cin >> m >> n) {
        vector<vector<int>> grid(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> grid[i][j];
            }
        }
        std::cout << unique_paths_with_obstacles(grid) << std::endl;
    }
    return 0;
}

