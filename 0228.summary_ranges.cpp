#include <iostream>
#include <string>
#include <vector>

using std::vector, std::string;

// 更好的滑动窗口，但是 RE
vector<string> summary_range(vector<int>& nums)
{
    vector<string> res;

    int r = -1;
    int n = nums.size();

    while (++r < n){
        int l = r;
        // 不能这么写啊，过不了 addresssanitizer
        while (nums[r+1] - nums[r] == 1) ++r;
        string tmp = std::to_string(nums[l]);
        if (r != l) {
            tmp += "->";
            tmp += std::to_string(nums[r]);
        }
        res.push_back(tmp);
    }

    return res;
}

// 有序数组
vector<string> _summary_range(vector<int>& nums)
{
    int n = nums.size();

    int l = 0;
    int r = 1;

    vector<string> res;

    if (n == 0) {
        return res;
    } else if (n == 1) {
        res.push_back(std::to_string(nums[0]));
        return res;
    }

    // 为了不处理最后的那一部分，直接往原数组尾处插入一个数字
    // 我这里插入 nums[0]，因为这样肯定也不满足题意
    nums.push_back(nums[0]);
    ++n;

    while (r < n) {

        // 更新答案的时候左缩
        // 顶不住了，测试数据隔这儿恶心人呢
        // [-2147483648,-2147483647,2147483647]
        // if (r <= n && nums[r] != (long long)nums[r-1] + 1) {
        if (r <= n && nums[r] - nums[r-1] != 1) {
            string tmp = std::to_string(nums[l]);
            if (r != l + 1) {
                tmp += "->";
                tmp += std::to_string(nums[r - 1]);
            }
            res.push_back(tmp);
            l = r;
        }

        // 右扩
        ++r;
    }

    // 数组尾插入数字后，就不需要再写这部分的处理了
    // if (r == n) {
    //     string tmp = std::to_string(nums[l]);
    //     if (r != l + 1) {
    //         tmp += "->";
    //         tmp += std::to_string(nums[r - 1]);
    //     }
    //     res.push_back(tmp);
    //     l = r;
    // }

    // 记得把数组恢复
    nums.pop_back();

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0228.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        vector<string> res = summary_range(nums);
        std::cout << "[";
        for (int i = 0; i < res.size(); ++i) {
            std::cout << res[i] << ", ";
        }
        std::cout << "]" <<  std::endl;
    }

    return 0;
}
