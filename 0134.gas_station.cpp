#include <iostream>
#include <vector>

using std::vector;

int can_complete_circuit(vector<int>& gas, vector<int>& cost)
{
    int n = gas.size();
    int sum = 0;
    int msum = 0;
    int pos = 0;

    // 因为题目中说了，保证答案唯一
    // 那么找到剩余汽油最多的站即可
    for (int i = 0; i < n; ++i) {
        sum += (gas[i] - cost[i]);
        if (sum < msum) {
            msum = sum;
            pos = i + 1;
        }
    }

    // 用 sum 来判断究竟能够环绕一圈
    if (sum < 0) return -1;

    // 环形的话，最后一站的下一站是 0
    return pos == n ? 0 : pos;
}

int main () {
#ifdef LOCAL
    freopen("0134.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> gas(n, 0);
        vector<int> cost(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> gas[i];
        }
        for (int i = 0; i < n; ++i) {
            std::cin >> cost[i];
        }
        std::cout << can_complete_circuit(gas, cost) << std::endl;
    }

    return 0;
}
