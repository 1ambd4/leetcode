#include <cmath>
#include <iostream>
#include <vector>

using std::vector;

// 树状数组能过的话，分块大概率也行
class NumArray {
public:
    NumArray(vector<int>& nums)
    {
        int n = nums.size();
        this->size = std::sqrt(n);
        this->nums = nums;
        this->sum.resize((n + size - 1) / size);
        for (int i = 0; i < n; ++i) {
            this->sum[ i / size] += nums[i];
        }
    }

    void update(int index, int val)
    {
        sum[index / size] += val - nums[index];
        nums[index] = val;
    }

    int sum_range(int left, int right)
    {
        int b1 = left / size;
        int i1 = left % size;
        int b2 = right / size;
        int i2 = right % size;

        if (b1 == b2) {
            int sum = 0;
            for (int i = i1; i <= i2; ++i) {
                sum += nums[b1 * size + i];
            }
            return sum;
        }

        int sum1 = 0;
        for (int i = i1; i < size; ++i) {
            sum1 += nums[b1 * size + i];
        }
        int sum2 = 0;
        for (int i = 0; i <= i2; ++i) {
            sum2 += nums[b2 * size + i];
        }
        int sum3 = 0;
        for (int i = b1 + 1; i < b2; ++i) {
            sum3 += sum[i];
        }

        return sum1 + sum2 + sum3;
    }

private:
    int size = 0;
    vector<int> sum;
    vector<int> nums;
};

// 还得是树状数组
class _NumArray {
public:
    _NumArray(vector<int>& nums)
    {
        this->n = nums.size();
        this->nums = nums;
        this->tree.resize(n+1, 0);
        for (int i = 0; i < n; ++i) {
            add(i + 1, nums[i]);
        }
    }

    void update(int index, int val)
    {
        int delta = val - nums[index];
        add(index + 1, delta);
        nums[index] = val;
    }

    int sum_range(int left, int right)
    {
        return query(right + 1) - query(left);
    }

private:
    vector<int> tree;
    vector<int> nums;
    int n = 0;

    int lowbit(int x)
    {
        return x & -x;
    }

    int query(int x)
    {
        int ans = 0;
        for (int i = x; i > 0; i -= lowbit(i)) {
            ans += tree[i];
        }
        return ans;
    }

    void add(int x, int u)
    {
        for (int i = x; i <= n; i += lowbit(i)) {
            tree[i] += u;
        }
    }
};

// 用差分在线的处理前缀和？
class __NumArray {
public:
    __NumArray(vector<int>& nums)
    {
        this->n = nums.size();
        this->presum = vector<int>(n, 0);
        this->nums = nums;

        presum[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            presum[i] = presum[i-1] + nums[i];
        }
    }

    void update(int index, int val)
    {
        int delta = nums[index] - val;
        for (int i = index; i < n; ++i) {
            presum[i] -= delta;
        }
        nums[index] = val;
    }

    int sum_range(int left, int right)
    {
        return presum[right] - (left == 0 ? 0 : presum[left-1]);
    }
private:
    vector<int> presum;
    vector<int> nums;
    int n = 0;
};

int main()
{
    vector<int> nums {1, 3, 5};
    NumArray* obj = new NumArray(nums);
    std::cout << obj->sum_range(0, 2) << std::endl;
    obj->update(1, 2);
    std::cout << obj->sum_range(0, 2) << std::endl;

    return 0;
}
