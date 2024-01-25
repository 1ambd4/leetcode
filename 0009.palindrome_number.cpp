#include <iostream>
#include <string>

bool is_palindrome(int x)
{
    if (x < 0) return false;

    int rx = 0, tx = x;
    while (tx > 0) {
        rx = rx * 10 + tx % 10;
        tx /= 10;
    }

    return rx == x;
}

bool _is_palindrome(int x)
{
    if (x < 0) return false;

    std::string s = std::to_string(x);
    int n = s.size();

    int l = 0, r = n - 1;
    while (l < r) {
        if (s[l] != s[r]) {
            return false;
        }
        ++l;
        --r;
    }

    return true;
}

int main () {
#ifdef LOCAL
    freopen("0009.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        std::cout << _is_palindrome(n) << std::endl;
    }

    return 0;
}
