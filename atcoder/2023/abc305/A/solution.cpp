#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    const auto ans = [&]() -> int {
        int hi = 0;

        for (int i = 0; i <= 100; i += 5) {
            if (abs(i - N) < abs(hi - N)) {
                hi = i;
            }
        }

        return hi;
    }();

    cout << ans << '\n';
    return 0;
}
