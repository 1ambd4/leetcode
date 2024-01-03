#include <iostream>
#include <vector>

using std::vector;

int majority_element(vector<int>& nums)
{
    int n = nums.size();

    int num = nums[0];
    int cnt = 0;

    for (int i = 0; i < n; ++i) {
        if (nums[i] == num) {
            ++cnt;
        } else {
            if (cnt >= 1) {
                --cnt;
            } else {
                num = nums[i];
                cnt = 1;
            }
        }
    }

    return num;
}

int main () {
#ifdef LOCAL
    freopen("0169.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << majority_element(nums) << std::endl;
    }

    return 0;
}
