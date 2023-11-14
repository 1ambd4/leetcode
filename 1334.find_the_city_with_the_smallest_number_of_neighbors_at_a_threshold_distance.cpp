#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using std::vector;

// Floyd
int find_the_city(int n, vector<vector<int>>& edges, int d)
{
    vector<vector<int>> dis(n, vector<int>(n, std::numeric_limits<int>::max() >> 1));
    for (int i = 0; i < n; ++i) {
        dis[i][i] = 0;
    }
    for (const auto edge: edges) {
        int u = edge[0];
        int v = edge[1];
        int w = edge[2];
        dis[u][v] = w;
        dis[v][u] = w;
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }

    int min = std::numeric_limits<int>::max();
    int res = -1;
    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        for (int j = 0; j < n; ++j) {
            if (dis[i][j] <= d) {
                cnt++;
            }
        }
        if (cnt <= min) {
            min = cnt;
            res = i;
        }
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("1334.in", "r", stdin);
#endif
    int n = 0, t = 0, d = 0;
    while (std::cin >> n >> t >> d) {
        vector<vector<int>> edges(t, vector<int>(3, 0));
        for (int i = 0; i < t; ++i) {
            std::cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
        }
        std::cout << find_the_city(n, edges, d) << std::endl;
    }

    return 0;
}
