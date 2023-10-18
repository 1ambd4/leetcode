#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>
#include <queue>

long long max_kelements(std::vector<int>& nums, int k)
{
    std::priority_queue<int, std::vector<int>, std::less<int>> q(nums.begin(), nums.end());

    long long res = 0;
    for (int i = 0; i < k; ++i) {
        int max = q.top();
        q.pop();
        res += max;
        q.push(std::ceil(max / 3.0));
    }

    return res;
}

int main()
{
#ifdef LOCAL
    freopen("2530.in", "r", stdin);
#endif
    int n = 0, k = 0;
    while (std::cin >> n >> k) {
        std::vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << max_kelements(nums, k) << std::endl;
    }
}
