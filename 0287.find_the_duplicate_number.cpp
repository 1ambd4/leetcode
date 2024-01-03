#include <iostream>
#include <vector>

using std::vector;

// 共 n+1 个数字，且范围在 [1, n] 之间
int find_duplicate(vector<int>& nums)
{
    int slow = 0, fast = 0;

    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);

    slow = 0;
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }

    return slow;
}

int main () {
#ifdef LOCAL
    freopen("0287.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        std::cout << find_duplicate(nums) << std::endl;
    }

    return 0;
}
