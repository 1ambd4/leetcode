#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using std::vector, std::string;

vector<string> letter_combinations(string digits)
{
    std::unordered_map<char, string> m {
        {'1', ""},     {'2', "abc"}, {'3', "def"},
        {'4', "ghi"},  {'5', "jkl"}, {'6', "mno"},
        {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"},
    };

    vector<string> res;
    string path;
    int n = digits.size();

    if (n == 0) return res;

    auto backtracking = [&digits, &res, &path, &m, n](auto&& self, int k) -> void {
        // 不能 if (k == n) 那样是求子集了？
        if (path.size() == n) {
            res.push_back(path);
            return ;
        }

        for (int i = k; i < n; ++i) {
            for (const auto c : m[digits[i]]) {
                path.push_back(c);
                self(self, i + 1);
                path.pop_back();
            }
        }
    };

    backtracking(backtracking, 0);

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0017.in", "r", stdin);
#endif
    string digits;
    while (std::cin >> digits) {
        vector<string> res = letter_combinations(digits);
        for (const auto& e : res){
            std::cout << e << std::endl;
        }
    }

    return 0;
}
