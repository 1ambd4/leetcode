#include <iostream>
#include <string>
#include <vector>

using std::vector, std::string;

// 状态机写法
// https://mp.weixin.qq.com/s/r9pbkMyFyMAvmkf4QnL-1g
class KMP {
public:
    KMP(string pat) : pat(pat)
    {
        int n = pat.size();

        // f[j][c]：状态 j 读入字符 c 转到的状态
        f = vector<vector<int>>(n, vector<int>(256));

        // base case，从状态0读入串的第一个字符转入状态1
        f[0][pat[0]] = 1;

        int x = 0; // 影子状态初始为0
        for (int j = 1; j < n; ++j) {
            for (int c = 0; c < 256; ++c) {
                f[j][c] = f[x][c];
            }
            // 在状态j上遇到字符pat[j]则转移到状态j+1
            // 为啥是j+1呢？其实无所谓的，这里就是方便嘛
            // 顺序的读取pat里的字符，按序构造状态机
            f[j][pat[j]] = j + 1;
            // 同时更新所谓的影子状态，一样是读入字符c后转移到新的状态
            x = f[x][pat[j]];
        }
    }

    int search(string txt)
    {
        int n = txt.size();
        int m = pat.size();

        for (int i = 0, j = 0; i < n; ++i) {
            // 计算下一个状态
            j = f[j][txt[i]];
            // 到达终止状态，返回结果
            if (j == m) return i - m + 1;
        }

        return -1;
    }
private:
    string pat;
    vector<vector<int>> f;
};

int strstr(string haystack, string needle)
{
    KMP kmp(needle);
    return kmp.search(haystack);
}

int main () {
#ifdef LOCAL
    freopen("0028.in", "r", stdin);
#endif
    string s1 {""};
    string s2 {""};
    while (std::cin >> s1 >> s2) {
        std::cout << strstr(s1, s2) << std::endl;
    }

    return 0;
}
