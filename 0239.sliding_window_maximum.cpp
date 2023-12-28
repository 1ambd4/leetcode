#include <cstdio>
#include <deque>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using std::vector;

// 顺着方法一的思路继续优化
// 方法一有一些看起来不那么必须的操作
// 即更新结果的时候，需要判断队头元素是否超出了窗口
// 那么，是否可以把这一部分优化掉呢？
// 换句话说，即让这些需要被弹出的元素不入队
// 考虑这样一种情况，窗口内的两个下标 i 和 j，有 i < j
// 如果 nums[i] < nums[j]，会如何呢？
// 显然，只要 nums[j] 还在窗口内
// nums[i] 一定不会是滑动窗口的最大值
// 那么，就可以用一个队列存储这里的 j
// 在队列里，按照下标从小到大的顺序存储
// 且它们在数组 nums 中对应的值是严格单调递减的
//
// 当窗口滑动，插入元素时，为了保持队列性质
// 会不断的将新元素和队尾元素做比较
// 如果前者大于后者，那么队尾的元素就可以被移除了
// 同时，还要不断的从队首弹出元素，知道队首元素在窗口中
//
// 为了同时操作队首和队尾，考虑使用双端队列
// 满足这种性质的双端队列一般称为单调队列
vector<int> max_sliding_window(vector<int>& nums, int k)
{
    int n = nums.size();
    std::deque<int> q;

    for (int i = 0; i < k; ++i) {
        while (!q.empty() && nums[i] >= nums[q.back()]) {
            q.pop_back();
        }
        q.push_back(i);
    }

    vector<int> res = { nums[q.front()] };
    for (int i = k; i < n; ++i) {
        while (!q.empty() && nums[i] >= nums[q.back()]) {
            q.pop_back();
        }
        q.push_back(i);
        while (q.front() <= i - k) {
            q.pop_front();
        }
        res.push_back(nums[q.front()]);
    }

    return res;
}


// 最先想到的是大根堆，那么也就是 cpp 里的优先队列
// 根实模拟可能会想插入一个的同时弹出一个
// 就像下面用 deque 模拟一样
// 但实际上是不需要的
// 可以只管往里添加，只在要往结果里添加答案的时候
// 依次的判断优先队列队头的元素是否已经不在窗口内
// 即使某次插入的是一个很小的元素，导致一直在队尾，使得窗口大于 k 因为没有关系
// 因为我们要求的是窗口中的最大元素，个数多不多无所谓
// 只要添加到结果的时候，将队头所有不在窗口中的元素弹出即可
// 那么，最后队头剩下的就是窗口里的最大值了
// 当然，这么写，需要保存额外的信息，即当前元素 num 在数组中的下标
vector<int> _max_sliding_window(vector<int>& nums, int k)
{
    int n = nums.size();

    std::priority_queue<std::pair<int, int>> q;
    for (int i = 0; i < k; ++i) q.emplace(nums[i], i);

    vector<int> res = {q.top().first};

    for (int i = k; i < n; ++i) {
        q.emplace(nums[i], i);
        while (q.top().second <= i - k) {
            q.pop();
        }
        res.push_back(q.top().first);
    }

    return res;
}

class Deque {
public:
    void push(int x)
    {
        while (!q.empty() && q.back() < x) {
            q.pop_back();
        }
        q.push_back(x);
    }

    void pop(int x)
    {
        if (q.front() == x) {
            q.pop_front();
        }
    }

    int max()
    {
        return q.front();
    }
private:
    std::deque<int> q;
};

// 这题怎么说呢，很奇怪
// 难在如何动态的判断 k 个数字中的最大值
vector<int> __max_sliding_window(vector<int>& nums, int k)
{
    int n = nums.size();

    Deque window;
    vector<int> res;

    for (int i = 0; i < n; ++i) {
        if (i < k - 1) {
            window.push(nums[i]);
        } else {
            window.push(nums[i]);
            res.push_back(window.max());
            window.pop(nums[i]);
        }
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0239.in", "r", stdin);
#endif
    int n = 0, k = 0;
    while (std::cin >> n >> k) {
        vector<int> nums(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
        vector<int> res = max_sliding_window(nums, k);
        for (int i = 0; i < res.size(); ++i) {
            printf(",%d" + !i, res[i]);
        }
        printf("\n");
    }

    return 0;
}
