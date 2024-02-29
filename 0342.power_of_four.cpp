#include <iostream>

// 4 的幂一定是 2 的幂
// 4 的幂和 2 的幂的二进制表示都有明显的规律
// 2 的幂的二进制表示是只有一位为 1
// 4 的幂的二进制表示同样只有一位为 1，但只能是奇数位
// 故可以使用 0x5 = 0101b 来进行检测
bool is_power_of_four(int n)
{
    if (n < 0 || n & (n-1)) {
        return false;
    }
    return n & 0x55555555;
}

bool _is_power_of_four(int n)
{
    if (n < 1) return false;
    if (n == 1) return true;

    if (n % 4 != 0) return false;
    else return _is_power_of_four(n/4);
}

int main () {
#ifdef LOCAL
    freopen("0342.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        std::cout << is_power_of_four(n) << std::endl;
    }

    return 0;
}
