#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::vector, std::string;

// 这个题怎么这么麻烦啊
vector<string> full_justify(vector<string>& words, int width)
{
    vector<string> res;

    // 分行
    vector<vector<string>> tmps;
    int cnt = 0;
    tmps.push_back(vector<string>());
    for (const auto word: words) {
        int n = word.size();
        if ((cnt == 0 && n == width) || cnt + 1 + n <= width) {
            tmps.back().push_back(word);
            if (cnt == 0) cnt += n;
            else cnt += (1 + n);
        } else {
            tmps.push_back(vector<string>());
            tmps.back().push_back(word);
            cnt = n;
        }
    }

    // 合并
    // 最后一行左对齐
    // 只有一个单词的行也是左对齐
    int n = tmps.size();
    for (int i = 0; i < n; ++i) {
        int s = 0;
        int t = tmps[i].size();
        for (int j = 0; j < t; ++j) {
            s += tmps[i][j].size();
        }

        bool align = true;
        if (i == n - 1) align = false;
        if (t == 1) align = false;

        string tmp {tmps[i][0]};
        if (align) {
            int a = (width - s) / (t - 1);
            int b = width - s - a * (t - 1);
            for (int j = 1; j < t; ++j) {
                if (j <= b) tmp += " ";
                for (int k = 0; k < a; ++k) {
                    tmp += " ";
                }
                tmp += tmps[i][j];
            }
        } else {
            int p = 0;
            for (int j = 1; j < t; ++j) {
                tmp += " ";
                ++p;
                tmp += tmps[i][j];
            }
            for (int j = 0; j < width - s - p; ++j) {
                tmp += " ";
            }
        }
        res.push_back(tmp);
    }

    return res;
}

int main () {
#ifdef LOCAL
    freopen("0068.in", "r", stdin);
#endif
    std::string s {""};
    std::string i {""};
    while (std::getline(std::cin, s)) {
        std::getline(std::cin, i);
        int n = std::stoi(i);
        vector<string> words;
        std::stringstream ss(s);
        std::string tmp;
        while (ss >> tmp) {
            words.push_back(tmp);
        }
        vector<string> res = full_justify(words, n);
        for (const auto& s : res) {
            std::cout << s << std::endl;
        }
    }

    return 0;
}
