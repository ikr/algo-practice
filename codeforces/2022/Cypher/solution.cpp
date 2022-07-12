#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) {
            cin >> x;
        }

        for (int j = 0; j < n; ++j) {
            int k;
            cin >> k;

            string ms;
            cin >> ms;

            assert(sz(ms) == k);

            for (const auto m : ms) {
                if (m == 'D') {
                    ++xs[j];
                } else {
                    assert(m == 'U');
                    --xs[j];
                }

                xs[j] %= 10;
                xs[j] += 10;
                xs[j] %= 10;
            }
        }

        cout << xs << '\n';
    }

    return 0;
}
