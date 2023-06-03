#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr array Level{1000,       10'000,      100'000,      1'000'000,
                             10'000'000, 100'000'000, 1'000'000'000};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int x;
    cin >> x;

    const auto ans = [&]() -> int {
        for (int i = 0; i < sz(Level); ++i) {
            if (x < Level[i]) {
                const auto m = Level[i] / 1000;
                return (x / m) * m;
            }
        }

        assert(false && "/o\\");
        return -1;
    }();

    cout << ans << '\n';
    return 0;
}
