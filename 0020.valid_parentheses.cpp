#include <iostream>
#include <string>
#include <stack>

using std::string, std::stack;

bool is_valid(string s)
{
    stack<char> stk;

    auto pair = [](char c) -> char {
        if (c == ')') {
            return '(';
        } else if (c == '}') {
            return '{';
        } else {
            return '[';
        }
    };

    for (const auto c : s) {
        if (c == '(' || c == '{' || c == '[') {
            stk.push(c);
        } else {
            char u = pair(c);
            if (stk.empty() || stk.top() != u) {
                return false;
            } else {
                stk.pop();
            }
        }
    }

    return stk.empty();
}

int main () {
#ifdef LOCAL
    freopen("0020.in", "r", stdin);
#endif
    string s;
    while (std::cin >> s) {
        std::cout << is_valid(s) << std::endl;
    }

    return 0;
}
