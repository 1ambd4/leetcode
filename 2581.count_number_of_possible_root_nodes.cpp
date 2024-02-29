#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <set>

using std::vector, std::queue, std::set;

int root_count(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k)
{
    typedef long long ll;
    int n = edges.size() + 1;

    vector<vector<int>> g(n, vector<int>());
    for (auto &edge : edges) {
        int u = edge[0];
        int v = edge[1];
        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::unordered_set<ll> s;
    for (auto& guess : guesses) {
        int u = guess[0];
        int v = guess[1];
        s.insert((ll) u << 32 | v);  // 两个int压缩成一个long long
    }

    int ans = 0;
    int cnt = 0;

    // dfs(u, p): 以 u 为起点 dfs，其中 p 是 u 的父节点
    // 即存在有向边 p -> u
    std::function<void(int, int)> dfs = [&](int u, int p) {
        for (auto v : g[u]) {
            if (v != p) {
                cnt += s.count((ll) u << 32 | v);  // 以 0 为根时，猜对了
                dfs(v, u);
            }
        }
    };
    dfs(0, -1);

    // 换根
    std::function<void(int, int, int)> reroot = [&](int u, int p, int cnt) {
        ans += cnt >= k;
        for (auto v : g[u]) {
            if (v != p) {
                reroot(v, u, cnt
                        - s.count((ll) u << 32 | v)   // 原来是对的，现在错了
                        + s.count((ll) v << 32 | u)); // 原来是错的，现在对了
            }
        }
    };

    reroot(0, -1, cnt);

    return ans;
}

// 他妈的，map 改 set，还是 TLE
int ____root_count(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k)
{
    int n = edges.size() + 1;

    vector<vector<int>> g(n, vector<int>());
    for (auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // 先以 0 为根跑一次拓扑排序
    // std::multimap<int, int> m;
    vector<set<int>> m(n, set<int>());

    vector<int> used(n, 0);
    queue<int> q;
    q.push(0);
    used[0] = 1;

    while (!q.empty()) {
        int t = q.size();
        for (int j = 0; j < t; ++j) {
            int u = q.front();
            q.pop();

            for (auto v : g[u]) {
                if (!used[v]) {
                    // m.insert({u, v});
                    m[u].insert(v);
                    q.push(v);
                    used[v] = 1;
                }
            }
        }
    }

    int res = 0;
    std::fill(used.begin(), used.end(), 0);

    used[0] = 1;
    auto dfs = [&g, k, &res, &guesses](auto&& self, int u, vector<int> used, vector<set<int>> m) -> void {
        int ans = 0;
        for (auto& guess : guesses) {
            int u = guess[0];
            int v = guess[1];

            if (m[u].count(v)) {
                ans++;
            }
        }
        if (ans >= k) res++;

        for (auto v : g[u]) {
            if (!used[v]) {
                used[v] = 1;
                // 把 u -> v 这条边改为 v -> u
                // auto ituv = m.begin();
                // while (ituv != m.end()) {
                //     if (ituv->first == u && ituv->second == v) {
                //         ituv = m.erase(ituv);
                //         break;
                //     } else {
                //         ituv++;
                //     }
                // }
                // m.insert({v, u});

                m[u].erase(v);
                m[v].insert(u);

                self(self, v, used, m);

                m[v].erase(u);
                m[u].insert(v);

                // 改回去
                // auto itvu = m.begin();
                // while (itvu != m.end()) {
                //     if (itvu->first == v && itvu->second == u) {
                //         itvu = m.erase(itvu);
                //         break;
                //     } else {
                //         itvu++;
                //     }
                // }
                // m.insert({u, v});
                // used[v] = 0;
            }
        }
    };

    dfs(dfs, 0, used, m);

    return res;
}

// 换根的时候，不用重跑一次拓扑排序
// 实际上，只会影响到新根和旧根之间的关系
// 还是 TLE 36/51
int ___root_count(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k)
{
    int n = edges.size() + 1;

    vector<vector<int>> g(n, vector<int>());
    for (auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // 先以 0 为根跑一次拓扑排序
    std::multimap<int, int> m;

    vector<int> used(n, 0);
    queue<int> q;
    q.push(0);
    used[0] = 1;

    while (!q.empty()) {
        int t = q.size();
        for (int j = 0; j < t; ++j) {
            int u = q.front();
            q.pop();

            for (auto v : g[u]) {
                if (!used[v]) {
                    m.insert({u, v});
                    q.push(v);
                    used[v] = 1;
                }
            }
        }
    }

    // 以 0 为根的时候先算一下答案
    // 不用捏，换根的时候一起算
    // int res = 0;
    // int tmp = 0;
    // for (auto& guess : guesses) {
    //     int u = guess[0];
    //     int v = guess[1];
    //     auto range = m.equal_range(u);
    //     for (auto it = range.first; it != range.second; ++it) {
    //         if (it->second == v) {
    //             ++tmp;
    //             break;
    //         }
    //     }
    //     if (tmp >= k) {
    //         res++;
    //         break;
    //     }
    // }

    //  清空数组的方法
    // std::fill(used.begin(), used.end(), 0);
    // used.assign(used.size(), 0);

    // 接着跑拓扑排序来换根
    // 不行，不能跑拓扑排序了，得深搜换根
    // q.push(0);
    // used[0] = 1;
    // while (!q.empty()) {
    //     int t = q.size();
    //     for (int j = 0; j < t; ++j) {
    //         int u = q.front();
    //         q.pop();
    //
    //         for (auto v : g[u]) {
    //             if (!used[v]) {
    //                 q.push(v);
    //                 used[v] = 1;
    //             }
    //         }
    //     }
    // }

    int res = 0;
    std::fill(used.begin(), used.end(), 0);

    used[0] = 1;
    auto dfs = [&g, k, &res, &guesses](auto&& self, int u, vector<int> used, std::multimap<int, int> m) -> void {
        int ans = 0;
        for (auto& guess : guesses) {
            int u = guess[0];
            int v = guess[1];
            auto range = m.equal_range(u);
            for (auto it = range.first; it != range.second; ++it) {
                if (it->second == v) {
                    ans++;
                    break;
                }
            }
        }
        if (ans >= k) res++;

        for (auto v : g[u]) {
            if (!used[v]) {
                used[v] = 1;
                // 把 u -> v 这条边改为 v -> u
                auto ituv = m.begin();
                while (ituv != m.end()) {
                    if (ituv->first == u && ituv->second == v) {
                        ituv = m.erase(ituv);
                        break;
                    } else {
                        ituv++;
                    }
                }
                m.insert({v, u});

                self(self, v, used, m);

                // 改回去
                auto itvu = m.begin();
                while (itvu != m.end()) {
                    if (itvu->first == v && itvu->second == u) {
                        itvu = m.erase(itvu);
                        break;
                    } else {
                        itvu++;
                    }
                }
                m.insert({u, v});
                // used[v] = 0;
            }
        }
    };

    dfs(dfs, 0, used, m);

    return res;
}

// 还是 TLE 33/51
int __root_count(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k)
{
    int n = edges.size() + 1;

    vector<vector<int>> g(n, vector<int>());
    for (auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
        // vector<vector<int>> m;
        std::multimap<int, int> m;

        vector<int> used(n, 0);
        queue<int> q;
        q.push(i);
        used[i] = 1;

        while (!q.empty()) {
            int t = q.size();
            for (int j = 0; j < t; ++j) {
                int u = q.front();
                q.pop();

                for (auto v : g[u]) {
                    if (!used[v]) {
                        // m.push_back({u, v});
                        m.insert({u, v});
                        q.push(v);
                        used[v] = 1;
                    }
                }
            }
        }

        // int t = 0;
        // for (auto& guess : guesses) {
        //     auto it = std::find(m.begin(), m.end(), guess);
        //     if (it != m.end()) t++;
        //     if (t >= k) {
        //         res++;
        //         break;
        //     }
        // }

        int t = 0;
        for (auto& guess : guesses) {
            int u = guess[0];
            int v = guess[1];
            auto range = m.equal_range(u);
            for (auto it = range.first; it != range.second; ++it) {
                if (it->second == v) {
                    t++;
                    break;
                }
            }
            if (t >= k) {
                res++;
                break;
            }
        }
    }

    return res;
}

// 树其实是有向图，那么本题就变成了无向图转有向图
// 跑 n 次拓扑排序就好了呀
// 但是是无向图版（
// 所以难点来到了建图
//
// TLE 29/51
int _root_count(vector<vector<int>>& edges, vector<vector<int>>& guesses, int k)
{
    int n = edges.size() + 1;

    vector<vector<int>> g(n, vector<int>());
    for (auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
        vector<vector<int>> m;

        vector<int> used(n, 0);
        queue<int> q;
        q.push(i);
        used[i] = 1;

        while (!q.empty()) {
            int t = q.size();
            for (int j = 0; j < t; ++j) {
                int u = q.front();
                q.pop();

                for (auto v : g[u]) {
                    if (!used[v]) {
                        m.push_back({u, v});
                        q.push(v);
                        used[v] = 1;
                    }
                }
            }
        }

        int t = 0;
        for (auto& guess : guesses) {
            auto it = std::find(m.begin(), m.end(), guess);
            if (it != m.end()) t++;
        }
        if (t >= k) res++;
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("2581.in", "r", stdin);
#endif
    int m = 0, n = 0, k = 0;
    while (std::cin >> m >> n >> k) {
        vector<vector<int>> edges(m, vector<int>(2, 0));
        vector<vector<int>> guess(n, vector<int>(2, 0));
        for (int i = 0; i < m; ++i) {
            std::cin >> edges[i][0] >> edges[i][1];
        }
        for (int i = 0; i < n; ++i) {
            std::cin >> guess[i][0] >> guess[i][1];
        }
        std::cout << root_count(edges, guess, k) << std::endl;
    }

    return 0;
}
