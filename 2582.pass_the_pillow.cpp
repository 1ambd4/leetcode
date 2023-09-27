#include <iostream>

int pass_the_pillow(int n, int t)
{
    int m = t / (n - 1);
    int r = t % (n - 1);

    if (m % 2 == 0) {
        return r + 1;
    } else {
        return n - r;
    }
}

int main()
{
#ifdef LOCAL
    freopen("2582.in", "r", stdin);
#endif
    int n = 0, t = 0;
    while (std::cin >> n >> t) {
        std::cout << pass_the_pillow(n, t) << std::endl;
    }
    return 0;
}

