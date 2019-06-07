#include <bits/stdc++.h>

using namespace std;

template <typename T> int intof(T x) { return static_cast<int>(x); }

optional<int> isqrt(int x) {
    const double accurate_sqrt = sqrt(x);

    return intof(floor(accurate_sqrt)) == intof(ceil(accurate_sqrt))
               ? make_optional(intof(trunc(accurate_sqrt)))
               : nullopt;
}

using XY = pair<int, int>;

int main() {
    int n;
    cin >> n;

    for (int i = 0; i != n; ++i) {
        int x;
        cin >> x;
    }
}
