#include <iostream>
#include <vector>
#include <utility>

using std::vector, std::pair;

// m x n 的方格，需要向下移动 m - 1 次，向右移动 n - 1 次
// 总计需要移动 m + n - 2 次
// 那么所求的方案数就等于在这 m + n - 2 次移动中，哪 m - 1 次向下移动
// 即 C(m-1, m+n-2)
int unique_paths(int m, int n)
{
    int ans = 1;

    for (int x = n, y = 1; y < m; ++x, ++y) {
        ans = ans * x / y;
    }

    return ans;
}


// 路径压缩
int _unique_paths(int m, int n)
{
    vector<int> dp(n, 1);

    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            dp[j] += dp[j-1];
        }
    }

    return dp[n-1];
}

// 移动什么的不就是状态转移么
int __unique_paths(int m, int n)
{
    vector<vector<int>> dp(m, vector<int>(n, 0));

    for (int i = 0; i < m; ++i) dp[i][0] = 1;
    for (int j = 0; j < n; ++j) dp[0][j] = 1;

    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }

    return dp[m-1][n-1];
}


// dfs 是真的好写啊，还不容易出错
int ___unique_paths(int m, int n)
{
    int cnt = 0;
    vector<vector<bool>> vis(m, vector<bool>(n, 0));

    vector<pair<int, int>> dirs = {
        {1, 0}, {0, 1},
    };

    auto adj = [&dirs, m, n](int x, int y) {
        vector<pair<int, int>> res;

        for (const auto& [dx, dy] : dirs) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
                continue;
            }
            res.push_back({nx, ny});
        }

        return res;
    };

    auto dfs = [&adj, &cnt, &vis, m, n](auto&& self, int x, int y) {
        if (x == m - 1 && y == n - 1) {
            ++cnt;
            return ;
        }

        if (vis[x][y]) return ;

        // vis[x][y] = true;

        for (const auto& [nx, ny] : adj(x, y)) {
            // 注意这里是 vis[x][y] 而不是 vis[nx][ny]
            vis[x][y] = true;
            self(self, nx, ny);
            vis[x][y] = false;
        }
    };

    dfs(dfs, 0, 0);

    return cnt;
}

int main()
{
#ifdef LOCAL
    freopen("0062.in", "r", stdin);
#endif
    int m = 0, n = 0;
    while (std::cin >> m >> n) {
        std::cout << unique_paths(m, n) << std::endl;
    }
    return 0;
}

