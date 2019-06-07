#include <bits/stdc++.h>

using namespace std;

using XY = pair<int, int>;

ostream &operator<<(ostream &os, const XY &p) {
    os << "(" << p.first << " " << p.second << ")";
    return os;
}

template <typename T> int intof(const T x) { return static_cast<int>(x); }

int square(const int x) { return x * x; }

optional<int> isqrt(const int x) {
    const double accurate_sqrt = sqrt(x);

    return intof(floor(accurate_sqrt)) == intof(ceil(accurate_sqrt))
               ? make_optional(intof(trunc(accurate_sqrt)))
               : nullopt;
}

int manhattan_distance(const XY &p1, const XY &p2) {
    return abs(p1.first - p2.first) + abs(p2.second - p2.second);
}

optional<int> euclidian_idistance(const XY &p1, const XY &p2) {
    return isqrt(square(p1.first - p2.first) + square(p1.second - p2.second));
}

int main() {
    int n{0};
    cin >> n;

    vector<XY> points;

    for (int i = 0; i != n; ++i) {
        int x{0};
        int y{0};
        cin >> x >> y;

        points.emplace_back(x, y);
    }

    assert(intof(points.size()) == n);

    int result = 0;

    for (int i = 0; i != n - 1; ++i) {
        for (int j = i + 1; j != n; ++j) {
            cout << "Checking " << points[i] << " " << points[j] << endl;

            const auto maybe_eucl = euclidian_idistance(points[i], points[j]);
            if (!maybe_eucl) continue;

            if (manhattan_distance(points[i], points[j]) == *maybe_eucl) {
                cout << "Match!" << endl;
                ++result;
            }
        }
    }

    cout << result << endl;
}
