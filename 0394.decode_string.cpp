#include <iostream>
#include <stack>
#include <string>
#include <utility>

using std::string;

// 类似求解：3*(1+2*(5+2))+67+(2-15(22+4))

// 数字存放在数字栈，字符串存放在字符串栈
// 遇到右括号就从数字栈里弹出一个数字
// 同时字符串栈弹出直到左括号为止

// https://leetcode.cn/problems/decode-string/solutions/19447/decode-string-fu-zhu-zhan-fa-di-gui-fa-by-jyd/?envType=study-plan-v2&envId=top-100-liked
// 感觉就是把递归用栈实现了
// 但递归解法里，因为有栈帧存储中间变量
// 对于输入分隔是：(重复次数，字符串)
// 则遇到 '[' 就得到 res = res + tmps * tmpn
// 而栈的解法里，对于输入分隔是：(字符串，重复次数)
// 可以看到，这里的重复次数是对于下一个解析对的
// 因而，需要在遇到 ']' 的时候，res = tmps + res * tmpn
string decode_string(string s)
{
    int n = s.size();
    int num = 0;
    string res {""};

    std::stack<std::pair<int, string>> stk;
    for (const auto c : s) {
        // 遇到数字就存入 num
        if (c >= '0' && c <= '9') {
            num = num * 10 + (c - '0');
        // 遇到左括号，压栈数字和字符串，同时清空原变量
        } else if (c == '[') {
            stk.push({num, res});
            num = 0;
            res = "";
        // 遇到右括号，出栈数字和字符串，进行拼接
        // res = last_res + cur_multi * res
        } else if (c == ']') {
            auto [tmpn, tmps] = stk.top();
            stk.pop();
            for (int i = 0; i < tmpn; ++i) {
                tmps = tmps + res;
            }
            res = tmps;
        } else {
            res += c;
        }
    }

    return res;
}




// 思路一样捏，处理的时候分类讨论
// 1.数字的话，记录就好
// 2.'[' 递归
// 3.']' 返回
// 3. char：直接添加
string _decode_string(string s)
{
    int n = s.size();

    auto decode = [&s, n](auto&& self, int& k) -> string {
        int num = 0;
        string res {""};

        while (k < n) {
            char c = s[k++];
            if (c >= '0' && c <= '9') {
                num = num * 10 + (c - '0');
            } else if (c == '[') {
                string tmp = self(self, k);
                for (int i = 0; i < num; ++i) {
                    res += tmp;
                }
                num = 0;
            } else if (c == ']') {
                break;
            } else {
                res += c;
            }
        }

        return res;
    };

    // 如果递归里改变了某个变量，那么该变量一般都是需要传引用的
    // 找这个错找了好久，难崩
    int k = 0;
    string res = decode(decode, k);
    return res;
}

int main () {
#ifdef LOCAL
    freopen("0394.in", "r", stdin);
#endif
    string s;
    while (std::cin >> s) {
        std::cout << decode_string(s) << std::endl;
    }

    return 0;
}
