#include <iostream>

// 进一步的，位运算优化
double my_pow(double x, int n)
{
    auto quick_mul = [](double x, long long n) -> double {
        double ans = 1;
        while (n > 0) {
            if (n & 1) {
                ans *= x;
            }
            x *= x;
            n >>= 1;
        }
        return ans;
    };

    long long N = n;
    return N >= 0 ? quick_mul(x, N) : (1.0 / quick_mul(x, -N));
}

// 依据递归版本，很容易写出迭代版本
double _my_pow(double x, int n)
{
    auto quick_mul = [](double x, long long n) -> double {
        double ans = 1;
        while (n > 0) {
            if (n % 2 == 1) {
                ans *= x;
            }
            x *= x;
            n /= 2;
        }

        return ans;
    };

    // 转 long long 是防止下面取相反数的时候爆 int
    long long N = n;
    return N >= 0 ? quick_mul(x, N) : (1.0 / quick_mul(x, -N));
}

// 递归版本，很好的解释了快速幂的原理
double __my_pow(double x, int n)
{
    if (n == 0) return 1;
    if (n == 1) return x;
    if (n == -1) return 1 / x;

    double half = my_pow(x, n / 2);
    double rest = my_pow(x, n % 2);
    return rest * half * half;
}

int main () {
#ifdef LOCAL
    freopen("0050.in", "r", stdin);
#endif
    double x = 0.0;
    int n = 0;
    while (std::cin >> x >> n) {
        std::cout << my_pow(x, n) << std::endl;
    }

    return 0;
}
