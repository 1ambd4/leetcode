#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>

using std::vector, std::pair;

bool check_valid_grid(vector<vector<int>>& grid)
{
    int n = grid.size();

    vector<pair<int, int>> dirs = {
        {2,1}, {2,-1}, {-2,1}, {-2,-1},
        {1,2}, {1,-2}, {-1,2}, {-1,-2},
    };

    auto adj = [n, &dirs](int x, int y) -> vector<pair<int, int>> {
        vector<pair<int, int>> res;
        for (const auto& [dx, dy] : dirs) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            res.emplace_back(nx, ny);
        }
        return res;
    };

    auto dfs = [n, &adj, &grid](auto&& self, int x, int y, int v) -> bool {

        if (v == n * n) return true;
        if (grid[x][y] != v) {
            return false;
        }

        bool valid = false;
        for (const auto& [nx, ny] : adj(x, y)) {
            valid |= self(self, nx, ny, v+1);
        }

        return valid;
    };

    return dfs(dfs, 0, 0, 0);
}

// 我还想这grid里的数字干嘛用的，原来得按顺序走啊，难崩
bool _check_valid_grid(vector<vector<int>>& grid)
{
    int n = grid.size();
    vector<vector<int>> dirs = {
        {2,1}, {2,-1}, {-2,1}, {-2,-1},
        {1,2}, {1,-2}, {-1,2}, {-1,-2},
    };

    bool valid = false;
    vector<vector<bool>> vis(n, vector<bool>(n, false));

    auto dfs = [&valid, &vis, &dirs, &grid, &n](auto&& self, int x, int y, int v) -> void {
        if (v == n * n) {
            valid = true;
            return ;
        }
        if (vis[x][y] || grid[x][y] != v) return ;

        vis[x][y] = true;
        for (auto& dir: dirs) {
            int nx = x + dir[0];
            int ny = y + dir[1];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
            self(self, nx, ny, v+1);
        }
    };

    dfs(dfs, 0, 0, 0);

    return valid;
}

int main()
{
#ifdef LOCAL
    freopen("2596.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<vector<int>> grid(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> grid[i][j];
            }
        }
        std::cout << check_valid_grid(grid) << std::endl;
    }
    return 0;
}

