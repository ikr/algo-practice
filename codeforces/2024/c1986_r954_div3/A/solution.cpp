#include <bits/stdc++.h>
using namespace std;

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
        vector<int> xs(3);
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));

        int result = INT_MAX;
        for (int a = xs[0]; a <= xs.back(); ++a) {
            result =
                min(result, abs(a - xs[0]) + abs(a - xs[1]) + abs(a - xs[2]));
        }
        cout << result << '\n';
    }

    return 0;
}
