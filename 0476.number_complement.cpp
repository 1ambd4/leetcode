#include <iostream>

// 补码的性质
// 有   a = b1110'0101
// 如果 b = b1111'1111
// 则 a^b = b0001'1010 即是a 的补数
int find_complement(int n)
{
    int mask = 1;
    while (mask < n) {
        mask <<= 1;
        mask += 1;
    }
    return (n ^ mask);
}

int main () {
#ifdef LOCAL
    freopen("0476.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        std::cout << find_complement(n) << std::endl;
    }

    return 0;
}
