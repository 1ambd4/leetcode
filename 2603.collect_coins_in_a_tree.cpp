#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using std::vector, std::queue, std::unordered_map;


// WAWAWA，不想改了捏
int _collect_the_coins(vector<int>& coins, vector<vector<int>>& edges)
{
    int n = coins.size();

    vector<int> ind(n, 0);
    vector<vector<int>> g(n, vector<int>());
    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        g[u].push_back(v);
        g[v].push_back(u);
        ++ind[u];
        ++ind[v];
    }

    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (ind[i] == 1 && coins[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : g[u]) {
            if (--ind[v] == 1 && coins[v] == 0) {
                q.push(v);
            }
        }
    }

    unordered_map<int, int> m;
    for (int i = 0; i < n; ++i) {
        if (ind[i] == 1 && coins[i] == 1) {
            for (auto v : g[i]) {
                ++m[v];
            }
        }
    }

    int p = -1, t = 0;
    for (int i = 0; i < n; ++i) {
        if (ind[i] <= 1 || m.count(i) != 0) {
            continue;
        }

        int cnt = 0;

        for (int v : g[i]) {
            if (m.count(v)) {
                cnt += m[v];
            }
        }

        if (cnt > t) {
            t = cnt;
            p = i;
        }
    }

    if (p == -1) {
        return 0;
    }

    int res = 0;
    vector<bool> vis(n, false);
    q.push(p);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = true;

        if (ind[u] <= 1 && m.count(u) != 0) {
            continue;
        }

        for (int v : g[u]) {
            if (!vis[v] && ind[v] > 1 && m.count(v) == 0) {
                q.push(v);
            }
        }
        ++res;
    }

    return (res - 1) * 2;
}

// 因为没有明确的根之类的，所以还是建无向图方便点
// 最外沿的点，也就是度为 1 的点，如果没有金币，那么显然是不用到达的，可以删去
// 删去之后，如果出现了新的非金币且度为 1 的节点，同样继续删去
// 直到删除干净，记一共删去了 k 个节点
//
// 那么此时度为 1 的节点都是有金币的了
// 题中说了金币的拾取范围是 2，那么这些度为 1 的金币节点实际上也是不需要到达的
// 只要达到其父节点的父节点即可拾取
// 那么其父节点呢？无论其有没有金币，都是不需要达到的，因为也在父节点的父节点的拾取范围里
// 记度为 1 的金币节点个数为 t，t 个度为 1 的金币节点共有 f 个父节点
//
// 因为要走回来，故而每个边至少走两次
// 那么最终的答案就是 ((n - 1) - k - t - f) * 2
//
// 为啥是 n - 1 呢？因为 n 个点有 n - 1 条边
// k 和 t 是容易求的
// 可 f 就没有那么直观了
// 那么此时无向图就派上用场了，前面一直再说父节点父节点，实际上应该叫做邻居节点
// 在树里，通过孩子节点定位到父节点是麻烦的
// 但在无向图里，简单得很
// 想确定 f，只要遍历 t 个度为 1 的金币节点，然后减去其邻居节点的度
// 如果某时刻其邻居节点的度减为了 1，那就在 f 上累加 1 即可
// 这样是可以做到不重不漏的
// 最后的结果记得特判一下所有节点都没有金币的情况
// 此时应该返回 0，而不是计算所得的 -2，-2 是多减了一次
int collect_the_coins(vector<int>& coins, vector<vector<int>>& edges)
{
    int n = coins.size();
    int res = n - 1;

    vector<int> ind(n, 0);
    vector<vector<int>> g(n, vector<int>());
    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        g[u].push_back(v);
        g[v].push_back(u);
        ++ind[u];
        ++ind[v];
    }

    queue<int> q;

    for (int i = 0; i < n; ++i) {
        if (coins[i] == 0 && ind[i] == 1) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        --res;

        for (int v : g[u]) {
            if (--ind[v] == 1 && coins[v] == 0) {
                q.push(v);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (ind[i] == 1 && coins[i] == 1) {
            q.push(i);
        }
    }
    res -= q.size();
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : g[u]) {
            if (--ind[v] == 1) {
                --res;
            }
        }
    }

    return std::max(res * 2, 0);
}

int main()
{
#ifdef LOCAL
    freopen("2603.in", "r", stdin);
#endif
    int n = 0, t = 0;
    while (std::cin >> n >> t) {
        vector<int> coins(n, 0);
        vector<vector<int>> edges(t, vector<int>(2, 0));

        for (int i = 0; i < n; ++i) {
            std::cin >> coins[i];
        }
        for (int i = 0; i < t; ++i) {
            std::cin >> edges[i][0] >> edges[i][1];
        }

        std::cout << collect_the_coins(coins, edges) << std::endl;
    }
    return 0;
}
