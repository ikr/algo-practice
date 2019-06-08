#include <bits/stdc++.h>

using namespace std;

using XY = pair<int, int>;

namespace std {
template <> struct hash<XY> {
    size_t operator()(const XY &p) const noexcept {
        return 31 * static_cast<size_t>(p.first) +
               static_cast<size_t>(p.second);
    }
};
} // namespace std

ostream &operator<<(ostream &os, const XY &p) {
    os << "(" << p.first << " " << p.second << ")";
    return os;
}

int main() {
    int n{0};
    cin >> n;

    unordered_map<int, size_t> counts_by_x;
    unordered_map<int, size_t> counts_by_y;
    unordered_map<XY, size_t> counts_by_point;

    size_t result = 0;
    for (int i = 0; i != n; ++i) {
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
