#include <iostream>
#include <vector>

#include "leetcode.h"

using std::vector;

void set_zeroes(vector<vector<int>>& matrix)
{
    int m = matrix.size();
    int n = matrix[0].size();

    vector<int> row(m, 0);
    vector<int> col(n, 0);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == 0) {
                row[i] = 1;
                col[j] = 1;
            }
        }
    }

    // for (int i = 0; i < m; ++i) {
    //     if (row[i] == 1) {
    //         for (int k = 0; k < n; ++k) {
    //             matrix[i][k] = 0;
    //         }
    //     }
    // }
    // for (int j = 0; j < n; ++j) {
    //     if (col[j] == 1) {
    //         for (int k = 0; k < m; ++k) {
    //             matrix[k][j] = 0;
    //         }
    //     }
    // }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (row[i] == 1 || col[j] == 1) {
                matrix[i][j] = 0;
            }
        }
    }
}

int main () {
#ifdef LOCAL
    freopen("0073.in", "r", stdin);
#endif
    int m = 0, n = 0;
    while (std::cin >> m >> n) {
        vector<vector<int>> matrix(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> matrix[i][j];
            }
        }
        set_zeroes(matrix);
        std::cout << matrix << std::endl;
    }

    return 0;
}
