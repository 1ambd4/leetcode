#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using std::vector;

class MedianFinder {
public:
    MedianFinder() = default;

    void addNum(int num)
    {
        // large 中数字多，那么新的数字应该是插入到 small 里的
        // 但是不知道新插入的数字就是算是大还是算小
        // 故而，可以先插入到 large 中，然后将 large 中的最小的弹出
        // 将这个弹出的插入 small 中即可
        if (large.size() > small.size()) {
            large.push(num);
            small.push(large.top());
            large.pop();
        } else {
            small.push(num);
            large.push(small.top());
            small.pop();
        }
    }

    double findMedian()
    {
        if (large.size() > small.size()) {
            return large.top();
        } else if (large.size() < small.size()) {
            return small.size();
        } else {
            return (large.top() + small.top()) / 2.0;
        }
    }

private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> large;
    std::priority_queue<int, std::vector<int>, std::less<int>> small;
};

int main () {
#ifdef LOCAL
    freopen("0295.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<int> nums(n, 0);
        for (int i = 0; i < n; ++i) {
            std::cin >> nums[i];
        }
    }

    return 0;
}
