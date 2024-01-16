#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

// 这题还和 62.unique_path 不太一样
// 那题初始化都是 1 就好，可以状态压缩
// 这题里就麻烦多了
int min_path_sum(vector<vector<int>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();

    vector<int> f(n, 0);
    f[0] = grid[0][0];
    for (int i = 1; i < n; ++i) f[i] = f[i-1] + grid[0][i];
    for (int i = 1; i < m; ++i) {
        f[0] += grid[i][0];
        for (int j = 1; j < n; ++j) {
            f[j] = std::min(f[j], f[j-1]) + grid[i][j];
        }
    }


    return f[n-1];
}

int _min_path_sum(vector<vector<int>>& grid)
{
    int m = grid.size();
    int n = grid[0].size();

    // f[i][j]: 从最左上角到当前位置的路径上的最小数字和
    vector<vector<int>> f(m, vector<int>(n, 0));
    f[0][0] = grid[0][0];
    for (int i = 1; i < m; ++i) f[i][0] = grid[i][0] + f[i-1][0];
    for (int i = 1; i < n; ++i) f[0][i] = grid[0][i] + f[0][i-1];

    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            f[i][j] = std::min(f[i-1][j], f[i][j-1]) + grid[i][j];
        }
    }

    return f[m-1][n-1];
}

int main () {
#ifdef LOCAL
    freopen("0064.in", "r", stdin);
#endif
    int m = 0, n = 0;
    while (std::cin >> m >> n) {
        vector<vector<int>> nums(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> nums[i][j];
            }
        }
        std::cout << min_path_sum(nums) << std::endl;
    }

    return 0;
}
