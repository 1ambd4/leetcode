#include <iostream>

// 求数根
// 树根的用途：
//     1.校验
//       两数字的和的数根等于两数字的树根的和，即满足结合律
//       故而可以检验计算的正确性
//     2.判断整除性
//       如果数根能被3或9整除，那么原数也能被3或9整除
//     3.可以计算模运算的同余
int add_digits(int n)
{
    return (n-1) % 9 + 1;
}

int _add_digits(int n)
{
    if (n < 10) return n;

    int t = 0;
    while (n > 0) {
        t += n % 10;
        n /= 10;
    }

    return add_digits(t);
}

int main () {
#ifdef LOCAL
    freopen("0258.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        std::cout << add_digits(n) << std::endl;
    }

    return 0;
}
