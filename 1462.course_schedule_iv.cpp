#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <unordered_set>
#include <stdint.h>

#include "leetcode.h"

using std::vector;

vector<bool> check_if_prerequisite(int n, vector<vector<int>>& p, vector<vector<int>>& q)
{
    vector<int> in(n, 0);
    vector<vector<int>> adj(n, vector<int>());
    // __int128_t?
    vector<intmax_t> pare(n, 0);
    vector<bool> ans;
    ans.reserve(n);
    intmax_t one = 1;

    for (auto& e : p) {
        int u = e[0], v = e[1];
        ++in[v];
        adj[u].push_back(v);
        pare[v] |= (one << u);
    }

    std::queue<int> Q;
    for (int i = 0; i < n; ++i) {
        if (in[i] == 0) Q.push(i);
    }

    for (int i = 0; i < n; ++i) {
        int u = Q.front(); Q.pop();
        for (auto& v: adj[u]) {
            if (!--in[v]) Q.push(v);
            pare[v] |= pare[u];
        }
    }

    for (const auto& e : q) {
        ans.push_back(pare[e[1]] & (one << e[0]));
    }

    return ans;
}


vector<bool> _check_if_prerequisite(int n, vector<vector<int>>& p, vector<vector<int>>& q)
{
    vector<bool> ans;
    ans.reserve(q.size());

    std::vector<std::vector<int>> m(n);

    for (const auto& e : p) {
        int u = e[0], v = e[1];
        m[u].push_back(v);
    }

    auto bfs = [&m](int u, int v) -> bool {
        std::queue<int> q;
        vector<bool> vis(m.size(), false);

        for (int i = 0; i < m[u].size(); ++i) q.push(m[u][i]);
        vis[u] = true;

        while (!q.empty()) {
            int f = q.front(); q.pop();
            if (f == v) return true;
            else {
                for (int i = 0; i < m[f].size(); ++i) q.push(m[f][i]);
                // q.push(f);
                vis[f] = true;
            }
        }

        return false;
    };

    for (const auto& e: q) {
        int u = e[0], v = e[1];
        ans.push_back(bfs(u, v));
    }

    return ans;
}

int main()
{
#ifdef LOCAL
    freopen("1462.in", "r", stdin);
#endif
    int N = 0, P = 0, Q = 0;
    while (std::cin >> N >> P >> Q) {
        std::vector<std::vector<int>> p(P, std::vector<int>(2, 0));
        std::vector<std::vector<int>> q(Q, std::vector<int>(2, 0));

        for (int i = 0; i < P; ++i) std::cin >> p[i][0] >> p[i][1];
        for (int i = 0; i < Q; ++i) std::cin >> q[i][0] >> q[i][1];

        std::vector<bool> ans = check_if_prerequisite(N, p, q);

        std::cout << ans << std::endl;
    }
    return 0;
}
