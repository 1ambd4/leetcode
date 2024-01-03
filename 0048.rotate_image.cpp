#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

// 先以主对角线翻转（即做转置
// 然后左右镜像
void rotate(vector<vector<int>>& matrix)
{
    int n = matrix.size();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }

    int m = n >> 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::swap(matrix[i][j], matrix[i][n-1-j]);
        }
    }
}

int main () {
#ifdef LOCAL
    freopen("0048.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> matrix[i][j];
            }
        }
        rotate(matrix);
        std::cout << matrix << std::endl;
    }

    return 0;
}
