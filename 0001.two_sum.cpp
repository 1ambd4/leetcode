#include <algorithm>
#include <array>
#include <iostream>
#include <utility>
#include <vector>

using std::vector, std::array;

vector<int> two_sum(vector<int>& nums, int target)
{
    int n = nums.size();
    vector<array<int, 2>> inums(n, array<int, 2>({0, 0}));
    for (int i = 0; i < n; ++i) {
        inums[i][0] = i;
        inums[i][1] = nums[i];
    }
    std::sort(inums.begin(), inums.end(), [](array<int, 2>& a, array<int, 2>& b) -> bool {
            return a[1] < b[1];
    });

    for (int i = 0; i < n; ++i) {
        int res = target - inums[i][1];
        int l = i + 1, r = n - 1;
        while (l < r) {
            int m = (l + r + 1) >> 1;
            if (inums[m][1] <= res) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        if (inums[l][1] == res) {
            return {inums[i][0], inums[l][0]};
        }
    }

    return {};
}

vector<int> _two_sum(vector<int>& nums, int target)
{
    int n = nums.size();
    vector<array<int, 2>> inums(n, array<int, 2>({0, 0}));
    for (int i = 0; i < n; ++i) {
        inums[i][0] = i;
        inums[i][1] = nums[i];
    }
    std::sort(inums.begin(), inums.end(), [](array<int, 2>& a, array<int, 2>& b){
            return a[1] < b[1];
    });

    int l = 0, r = n - 1;
    int t = 0;
    while ((t = inums[l][1] + inums[r][1]) != target) {
        if (t < target) {
            ++l;
        } else if (t > target) {
            --r;
        }
    }

    return {inums[l][0], inums[r][0]};
}


int main () {
#ifdef LOCAL
    freopen("0001.in", "r", stdin);
#endif
    int n = 0, t = 0;
    while (std::cin >> n >> t) {
        std::vector<int> nums(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        vector<int> res = two_sum(nums, t);
        std::cout << res[0] << " " << res[1] << std::endl;
    }

    return 0;
}
