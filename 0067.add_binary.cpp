#include <iostream>
#include <string>
#include <type_traits>

using std::string;

string add_binary(string s1, string s2)
{
    if (s1.size() < s2.size()) std::swap(s1, s2);
    int n1 = s1.size();
    int n2 = s2.size();
    int carry = 0;

    int i = 0, j = 0;
    for (i = n1-1, j = n2-1; j >= 0; --i, --j) {
        int a = s1[i] - '0';
        int b = s2[j] - '0';

        int tmp = a + b + carry;
        s1[i] = tmp % 2 + '0';
        carry = tmp / 2;
    }
    while (carry != 0 && i >= 0) {
        int a = s1[i] - '0';

        int tmp = a + carry;
        s1[i] = tmp % 2 + '0';
        carry = tmp / 2;
        --i;
    }
    if (carry != 0) {
        s1 = std::to_string(carry) + s1;
    }

    return s1;
}

// 写错了，遍历顺序反了
string _add_binary(string s1, string s2)
{
    if (s1.size() < s2.size()) std::swap(s1, s2);
    int n1 = s1.size();
    int n2 = s2.size();

    int carry = 0, i = 0;
    for (i = n2 - 1; i >= 0; --i) {
        int a = s1[i] - '0';
        int b = s2[i] - '0';

        int tmp = a + b + carry;
        s1[i] = tmp % 2 + '0';
        carry = tmp / 2;
    }
    while (carry != 0 && i < n1) {
        int a = s1[i] - '0';

        int tmp = a + carry;
        s1[i] = tmp % 2 + '0';
        carry = tmp / 2;
        ++i;
    }
    if (carry != 0) {
        s1 = std::to_string(carry) + s1;
    }

    return s1;
}

int main () {
#ifdef LOCAL
    freopen("0067.in", "r", stdin);
#endif
    string s1, s2;
    while (std::cin >> s1 >> s2) {
        std::cout << add_binary(s1, s2) << std::endl;
    }

    return 0;
}
