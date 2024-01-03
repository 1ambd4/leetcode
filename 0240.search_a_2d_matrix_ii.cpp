#include <iostream>
#include <vector>

using std::vector;

bool search_matrix(vector<vector<int>>& matrix, int target)
{
    int m = matrix.size();
    int n = matrix[0].size();

    int row = 0, col = m - 1;

    while (row < m && col >= 0 && col < n) {
        if (matrix[row][col] == target) {
            return true;
        } else if (matrix[row][col] > target) {
            col--;
        } else if (matrix[row][col] < target) {
            row++;
        }
    }

    return false;
}

int main () {
#ifdef LOCAL
    freopen("0240.in", "r", stdin);
#endif
    int n = 0, t = 0;
    while (std::cin >> n >> t) {
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> matrix[i][j];
            }
        }
        std::cout << search_matrix(matrix, t) << std::endl;
    }

    return 0;
}
