#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

using std::vector, std::unordered_map, std::array;

int first_complete_index(vector<int>& arr, vector<vector<int>>& mat)
{
    int m = mat.size();
    int n = mat[0].size();

    vector<int> row(m, 0);
    vector<int> col(n, 0);

    unordered_map<int, array<int, 2>> mp;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            mp.insert({mat[i][j], {i, j}});
        }
    }

    int res = -1;
    int cnt = 0;

    for (const auto v : arr) {
        auto [i, j] = mp[v];
        row[i]++;
        col[j]++;

        if (row[i] == n) {
            res = i;
        }
        if (col[j] == m) {
            if (res == -1) {
                res = j;
            } else if (j < i) {
                res = j;
            }
        }

        if (res != -1) {
            return cnt;
        }
        ++cnt;
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("2661.in", "r", stdin);
#endif
    int m = 0, n = 0;
    while (std::cin >> m >> n) {
        std::vector<int> arr(m * n, 0);
        std::vector<std::vector<int>> mat(m, std::vector<int>(n, 0));
        for (int i = 0; i < m * n; ++i) {
            std::cin >> arr[i];
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> mat[i][j];
            }
        }
        std::cout << first_complete_index(arr, mat) << std::endl;
    }
    return 0;
}
