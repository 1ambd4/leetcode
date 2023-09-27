#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <ranges>
#include <utility>

#include "leetcode.h"

using std::vector, std::pair;


vector<int> filter_restaurants(vector<vector<int>>& restaurants, int vegan_friendly, int max_price, int max_distance)
{
    vector<int> ans;

    auto end = std::partition(restaurants.begin(), restaurants.end(), [&](auto& v) {
            return (!vegan_friendly || v[2]) && v[3] <= max_price && v[4] <= max_distance;
        });
    std::sort(restaurants.begin(), end, [](auto& a, auto& b) {
            return pair{ a[1], a[0] } > pair{ b[1], b[0] };
        });
    std::transform(restaurants.begin(), end, back_inserter(ans), [](auto& v) {
            return v[0];
        });

    return ans;
}

// id, rating, vegan, price, distance
vector<int> _filter_restaurants(vector<vector<int>>& restaurants, int vegan_friendly, int max_price, int max_distance)
{
    vector<int> res;

    std::sort(restaurants.begin(), restaurants.end(), [](vector<int>& a, vector<int>& b){
        return a[1] != b[1] ? a[1] > b[1] : a[0] > b[0];
    });

    for (const auto& rest : restaurants) {
        if (rest[2] < vegan_friendly || rest[3] > max_price || rest[4] > max_distance) {
            continue;
        }
        res.push_back(rest[0]);
    }

    return res;
}

// id, rating, vegan, price, distance
vector<int> __filter_restaurants(vector<vector<int>>& restaurants, int vegan_friendly, int max_price, int max_distance)
{
    auto vegan = [vegan_friendly](vector<int>& rest) {
        if (vegan_friendly) {
            return rest[2] == 1;
        } else {
            return rest[2] != 1;
        }
    };

    auto price = [max_distance](vector<int>& rest) {
        return rest[3] <= max_distance;
    };

    auto distance = [max_distance](vector<int>& rest) {
        return rest[4] <= max_distance;
    };

    vector<int> res;

    // std::cout << res << std::endl;
    // map、filter、sort?

    return res;
}

int main()
{
#ifdef LOCAL
    freopen("1333.in", "r", stdin);
#endif
    int n = 0, v = 0, p = 0, d = 0;
    while (std::cin >> n >> v >> p >> d) {
        vector<vector<int>> r(n, vector<int>(5, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 5; ++j) {
                std::cin >> r[i][j];
            }
        }
        vector<int> res = _filter_restaurants(r, v, p, d);
        std::cout << res << std::endl;
    }
    return 0;
}

