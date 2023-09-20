#include <iostream>
#include <string>
#include <stack>

using std::string, std::stack;

bool is_valid(string s)
{
    stack<char> stk;

    for (auto c : s) {
        switch (c) {
            case 'b':
                if (stk.empty() || stk.top() != 'a') {
                    return false;
                }
            case 'a':
                stk.push(c);
                break;
            case 'c':
                if (stk.size() < 2) {
                    return false;
                }

                char b = stk.top();
                stk.pop();
                char a = stk.top();
                stk.pop();

                if (a != 'a' || b != 'b') {
                    return false;
                }
                break;
        }
        // if (c == 'a') {
        //     stk.push(c);
        // } else if (c == 'b') {
        //     if (stk.empty() || stk.top() != 'a') {
        //         return false;
        //     }
        //     stk.push(c);
        // } else if (c == 'c') {
        //     if (stk.size() < 2) {
        //         return false;
        //     }
        //
        //     char b = stk.top();
        //     stk.pop();
        //     char a = stk.top();
        //     stk.pop();
        //     if (a != 'a' || b != 'b') {
        //         return false;
        //     }
        // }
    }

    return stk.empty();
}


bool _is_valid(string s)
{
    int pos = 0;
    while ((pos = s.find("abc")) != -1) {
        s.erase(pos, 3);
    }
    return s.empty();
}


int main()
{
#ifdef LOCAL
    freopen("1003.in", "r", stdin);
#endif
    string s {""};
    while (std::cin >> s) {
        std::cout << is_valid(s) << std::endl;
    }
    return 0;
}
