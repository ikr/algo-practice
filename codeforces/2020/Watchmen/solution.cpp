#include <bits/stdc++.h>

using namespace std;

using ull_t = unsigned long long;
using XY = pair<int, int>;

namespace std {
template <> struct hash<XY> {
    ull_t operator()(const XY &p) const noexcept {
        return 31ULL * hash<int>{}(p.first) + hash<int>{}(p.second);
    }
};
} // namespace std

int main() {
    unsigned int n{0U};
    cin >> n;

    unordered_map<int, ull_t> counts_by_x;
    unordered_map<int, ull_t> counts_by_y;
    unordered_map<XY, ull_t> counts_by_point;

    ull_t result{0ULL};
    for (unsigned int i = 0U; i != n; ++i) {
        int x{0};
        int y{0};
        cin >> x >> y;

        const XY point = make_pair(x, y);

        result += counts_by_x[x] + counts_by_y[y] - counts_by_point[point];

        ++counts_by_x[x];
        ++counts_by_y[y];
        ++counts_by_point[point];
    }

    cout << result << endl;
}
