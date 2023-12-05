#include <cmath>
#include <iostream>
#include <vector>
#include <queue>

using std::vector, std::queue;

// 因为要求最小油耗，那么自然等到所有外层的人都来了再选择出发
long long minimum_fuel_cost(vector<vector<int>>& roads, int seats)
{
    int n = roads.size();
    vector<int> cnt(n + 1, 1);
    vector<vector<int>> mp(n + 1, vector<int>());

    vector<int> in(n + 1, 0);
    for (const auto& road : roads) {
        int u = road[0];
        int v = road[1];
        in[u]++;
        in[v]++;
        mp[u].push_back(v);
        mp[v].push_back(u);
    }

    long long cost = 0;

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (in[i] == 1) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // 去到相邻的第一个
        int v = mp[u][0];
        cost += std::ceil(1.0 * cnt[u] / seats);
        cnt[v] += cnt[u];

        // 这里就有点儿写错了，题目限定了有向无环联通图
        // 而且 n 个点 n-1 条边，那么必然是两两相连
        // 不存在一个点和多个点相连的情况（编号为 0 的节点除外
        for (const auto v : mp[u]) {
            in[v]--;
            if (in[v] == 1 && v != 0) {
                q.push(v);
            }
        }
    }

    return cost;
}

int main () {
#ifdef LOCAL
    freopen("2477.in", "r", stdin);
#endif
    int n = 0, k = 0;
    while (std::cin >> n >> k) {
        vector<vector<int>> roads(n, vector<int>(2, 0));
        for (int i = 0; i < n; ++i) {
            std::cin >> roads[i][0] >> roads[i][1];
        }
        std::cout << minimum_fuel_cost(roads, k) << std::endl;
    }

    return 0;
}
