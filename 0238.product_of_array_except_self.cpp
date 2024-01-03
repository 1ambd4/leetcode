#include <cstdio>
#include <iostream>
#include <vector>

using std::vector;

vector<int> product_except_self(vector<int>& nums)
{
    int n = nums.size();
    vector<int> ans(n, 0);

    int pre = 1, suf = 1;

    for (int i = 0; i < n; ++i) {
        ans[i] = pre;   // ans[i] 初始化为 1, 这里乘起来也是可以的
        pre *= nums[i]; // pre 为前缀乘积
    }

    for (int i = n - 1; i >= 0; --i) {
        ans[i] *= suf;
        suf *= nums[i]; // suf 为后缀乘积
    }

    return ans;
}

int main () {
#ifdef LOCAL
    freopen("0238.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        vector<int> res = product_except_self(nums);
        for (int i = 0; i < res.size(); ++i) {
            printf(",%d" + !i, res[i]);
        }
        std::cout << std::endl;
    }

    return 0;
}
