#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static const string CF{"codeforces"};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        assert(sz(xs) == sz(CF));
        int ans{};
        for (int i = 0; i < sz(xs); ++i) ans += CF[i] != xs[i];
        cout << ans << '\n';
    }

    return 0;
}
