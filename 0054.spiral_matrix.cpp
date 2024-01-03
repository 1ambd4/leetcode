#include <cstdio>
#include <iostream>
#include <vector>

using std::vector;

vector<int> spiral_order(vector<vector<int>>& matrix)
{
    int m = matrix.size();
    int n = matrix[0].size();
    vector<int> res;

    // 输出以 [l, r] 和 (m, n) 围起来的矩阵的最外圈的数字
    auto cycle = [&res, &matrix](auto&& self, int l, int m, int r, int n) -> void {
        if (m == 0 || n == 0) return ;
        if (l >= m || r >= n) return ;

        for (int i = r; i < n; ++i) {
            res.push_back(matrix[r][i]);
        }
        for (int j = l + 1; j < m; ++j) {
            res.push_back(matrix[j][n-1]);
        }
        // 剩下两边都需要判断一下，防止重复输出
        if (m - l != 1) {
            for (int i = n - 2; i >= r + 1; --i) {
                res.push_back(matrix[m-1][i]);
            }
        }
        if (n - r != 1) {
            for (int j = m - 1; j >= l + 1; --j) {
                res.push_back(matrix[j][l]);
            }
        }

        self(self, l+1, m-1, r+1, n-1);
    };

    cycle(cycle, 0, m, 0, n);

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0054.in", "r", stdin);
#endif
    int m = 0, n = 0;
    while (std::cin >> m >> n) {
        vector<vector<int>> matrix(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> matrix[i][j];
            }
        }
        vector<int> res = spiral_order(matrix);
        for (int i = 0; i < res.size(); ++i) {
            printf(",%d" + !i, res[i]);
        }
        std::cout << std::endl;
    }

    return 0;
}
