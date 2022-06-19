#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using tri = tuple<int, int, int>;

vector<tri> possible_summands(const int s) {
    vector<tri> result;

    for (int i = 1; i <= s; ++i) {
        for (int j = 1; j <= s; ++j) {
            if (i + j > s) break;

            for (int k = 1; k <= s; ++k) {
                if (i + j + k > s) break;
                if (i + j + k == s) result.emplace_back(i, j, k);
            }
        }
    }

    return result;
}

using ll = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int h1, h2, h3, w1, w2, w3;
    cin >> h1 >> h2 >> h3 >> w1 >> w2 >> w3;

    const auto h1s = possible_summands(h1);
    const auto h2s = possible_summands(h2);
    const auto h3s = possible_summands(h3);

    int result{};

    for (const auto &row1 : h1s) {
        if (get<0>(row1) >= w1) continue;
        if (get<1>(row1) >= w2) continue;
        if (get<2>(row1) >= w3) continue;

        for (const auto &row2 : h2s) {
            if (get<0>(row1) + get<0>(row2) >= w1) continue;
            if (get<1>(row1) + get<1>(row2) >= w2) continue;
            if (get<2>(row1) + get<2>(row2) >= w3) continue;

            for (const auto &row3 : h3s) {
                if (get<0>(row1) + get<0>(row2) + get<0>(row3) == w1 &&
                    get<1>(row1) + get<1>(row2) + get<1>(row3) == w2 &&
                    get<2>(row1) + get<2>(row2) + get<2>(row3) == w3) {
                    ++result;
                }
            }
        }
    }

    cout << result << '\n';
    return 0;
}
