#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

optional<string> do_it(string xs) {
    for (int i = 1; i < sz(xs); ++i) {
        if (xs[i - 1] != xs[i]) {
            swap(xs[i - 1], xs[i]);
            return xs;
        }
    }
    return nullopt;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        const auto r = do_it(std::move(xs));
        if (r) {
            cout << "YES\n" << *r << '\n';
        } else {
            cout << "NO" << '\n';
        }
    }

    return 0;
}
