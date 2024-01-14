#include <iostream>
#include <vector>
#include <string>

using std::vector, std::string;

vector<string> generate_parenthesis(int n)
{
    vector<string> res;
    string path;
    n *= 2;

    auto backtracking = [&res, &path, n](auto&& self, int k, int c) {
        if (c < 0) return ;

        if (path.size() == n && c == 0) {
            res.push_back(path);
            return ;
        }

        for (int i = k; i < n; ++i) {
            ++c;
            path.push_back('(');
            self(self, i + 1, c);
            path.pop_back();
            --c;

            --c;
            path.push_back(')');
            self(self, i + 1, c);
            path.pop_back();
            ++c;
        }
    };

    backtracking(backtracking, 0, 0);

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0022.in", "r", stdin);
#endif
    int n = 0;
    while (std::cin >> n) {
        vector<string> res = generate_parenthesis(n);
        for (const auto& e : res) {
            std::cout << e << std::endl;
        }
    }

    return 0;
}
