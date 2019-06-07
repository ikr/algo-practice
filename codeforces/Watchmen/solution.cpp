#include <bits/stdc++.h>

using namespace std;


using XY = pair<int, int>;

template <typename T> int intof(const T x) { return static_cast<int>(x); }

int square(const int x) {
    return x * x;
}

optional<int> isqrt(int x) {
    const double accurate_sqrt = sqrt(x);

    return intof(floor(accurate_sqrt)) == intof(ceil(accurate_sqrt))
               ? make_optional(intof(trunc(accurate_sqrt)))
               : nullopt;
}

int manhattan_distance(XY p1, XY p2) {
    return abs(p1.first - p2.first) + abs(p2.second - p2.second);
}

optional<int> euclidian_idistance(XY p1, XY p2) {
    return isqrt(square(p1.first - p2.first) + square(p1.second - p2.second));
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i != n; ++i) {
        int x;
        cin >> x;
    }
}
