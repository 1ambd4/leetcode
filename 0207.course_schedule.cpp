#include <iostream>
#include <queue>
#include <vector>

using std::vector;

// 题解真不错
// 对于图中的节点来说，可能存在三种状态：
// 1.未搜索，即还未到达过这个点
// 2.搜索中，即搜索过这个点，但还没有回溯回来
// 3.已完成，即搜索过这个点，且已经回溯完了
//
// 拓扑排序做的是什么呢，就是从入度为 0 的入手
// 而 dfs 可以这么理解，假使某条路径满足拓扑序
// 那么，回溯的路径（即搜索路径的逆序）刚好就是拓扑排序的结果
//
// 那么，每轮搜索开始时候，选取一个未搜索的节点开始 dfs
// 将当前搜索到的节点 u 标记未搜索中，遍历其所有的相邻节点 v：
// 1.如果 v 是未搜索，那么开始搜索 v，搜索完 v 肯定会回溯回 u 的
// 2.如果 v 是搜索中，说明在图中找到了一个环，因此不存在拓扑排序
// 3.如果 v 是已完成，显然，不需要做什么操作
// 如果 dfs 结束，每个节点都是已完成状态，则说明存在拓扑排序
bool can_finish(int n, vector<vector<int>>& pres)
{
    bool res = true;

    vector<vector<int>> g(n, vector<int>());
    vector<int> vis(n, 0);
    for (const auto& pre : pres) {
        int u = pre[0];
        int v = pre[1];
        g[v].push_back(u);
    }

    auto dfs = [&res, &vis, &g](auto&& self, int u) -> void {
        vis[u] = 1;
        for (const auto v : g[u]) {
            if (vis[v] == 0) {
                self(self, v);
                if (!res) return ;
            } else if (vis[u] == 1) {
                res = false;
                return ;
            }
        }
        vis[u] = 2;
    };

    for (int i = 0; i < n && res; ++i) {
        if (!vis[i]) {
            dfs(dfs, i);
        }
    }

    return res;
}

// 递归好难理解捏
bool __can_finish(int n, vector<vector<int>>& pres)
{
    bool res = true;

    vector<int> vis(n, 0);
    vector<int> path(n, 0);
    vector<vector<int>> g(n, vector<int>());
    for (const auto& pre: pres) {
        int u = pre[0];
        int v = pre[1];
        g[v].push_back(u);
    }

    auto traversal = [&g, &vis, &path, &res](auto&& self, int u) -> void {
        if (path[u]) res = false;

        if (vis[u] || !res) return ;

        vis[u] = 1;
        path[u] = 1;
        for (const auto& v: g[u]) {
            self(self, v);
        }
        path[u] = 0;
    };

    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            traversal(traversal, i);
        }
    }

    return res;
}

bool _can_finish(int n, vector<vector<int>>& pres)
{
    int res = 0;
    vector<vector<int>> g(n, vector<int>());
    vector<int> ind(n, 0);

    // v -> u
    for (const auto& pre : pres) {
        int u = pre[0];
        int v = pre[1];
        ind[u]++;
        g[v].push_back(u);
    }

    std::queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (ind[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ++res;
        for (const auto& v : g[u]) {
            ind[v]--;
            if (ind[v] == 0) {
                q.push(v);
            }
        }
    }

    return res == n;
}

int main () {
#ifdef LOCAL
    freopen("0207.in", "r", stdin);
#endif
    int t = 0, n = 0;
    while (std::cin >> t >> n) {
        vector<vector<int>> nums(n, vector<int>(2, 0));
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i][0] >> nums[i][1];
        }
        std::cout << can_finish(t, nums) << std::endl;
    }

    return 0;
}
