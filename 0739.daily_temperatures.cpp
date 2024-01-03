#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

#include "leetcode.h"

using std::vector;

vector<int> daily_temperatures(vector<int>& temps)
{
    int n = temps.size();

    std::unordered_map<int, int> mp;
    std::stack<int> stk;

    for (int i = n - 1; i >= 0; --i) {
        // 等于号记得加上鸭
        while (!stk.empty() && temps[stk.top()] <= temps[i]) {
            stk.pop();
        }
        mp[i] = stk.empty() ? 0 : stk.top() - i;
        stk.emplace(i);
    }

    vector<int> res;
    res.reserve(n);

    for (int i = 0; i < n; ++i) {
        res.push_back(mp[i]);
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0739.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        vector<int> res = daily_temperatures(nums);
        std::cout << res << std::endl;
    }

    return 0;
}
