#include <functional>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using std::priority_queue, std::vector, std::set;

class SmallestInfiniteSet {
public:
    SmallestInfiniteSet() : idx(1)
    {

    }

    int popSmallest()
    {
        int res = -1;
        // 最小值一定是在 nums 里的
        // popSmallest 的时候先判断 nums 是否为空
        if (!nums.empty()) {
            res = *nums.begin();
            nums.erase(res);
        } else {
            res = idx++;
        }
        return res;
    }

    void addBack(int num)
    {
        // addBack 的时候有三种情况
        // 1. num > idx
        // 2. num == idx - 1
        // 3. num < idx - 1
        if (num >= idx) {
            return ;
        } else if (num == idx - 1) {
            idx--;
        } else {
            nums.insert(num);
        }
    }

private:
    int idx;
    set<int> nums;
};


class _SmallestInfiniteSet {
public:
    _SmallestInfiniteSet() : idx(1)
    {
        vis.resize(1010, false);
    }

    int popSmallest()
    {
        int ans = -1;
        if (!q.empty()) {
            ans = q.top();
            q.pop();
            vis[ans] = false;
        } else {
            ans = idx++;
        }
        return ans;
    }

    void addBack(int num)
    {
        if (num >= idx || vis[num]) {
            return ;
        } else if (num == idx - 1) {
            idx--;
        } else {
            q.push(num);
            vis[num] = true;
        }
    }

private:
    // 无限集合中的元素为：q, [idx, +infinit]
    // 即优先队列 q 维护不连续的那部分
    // 而优先队列可以有重复元素，故而需要用 vis 标记一下是否已经在优先队列里了
    // 当然，用 set 也行
    int idx;
    vector<bool> vis;
    priority_queue<int, vector<int>, std::greater<int>> q;
};

int main () {
#ifdef LOCAL
    // freopen("2336.in", "r", stdin);
#endif

    SmallestInfiniteSet ss {};
    std::cout << ss.popSmallest() << std::endl;
    std::cout << ss.popSmallest() << std::endl;
    ss.addBack(3);
    std::cout << ss.popSmallest() << std::endl;
    ss.addBack(2);
    std::cout << ss.popSmallest() << std::endl;
    std::cout << ss.popSmallest() << std::endl;

    return 0;
}
