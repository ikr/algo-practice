#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_possible_apple_weight(const vector<int> &xs) { return -1; }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<int> xs(2 * N - 1);
        for (auto &x : xs) cin >> x;

        cout << "Case #" << i << ": " << min_possible_apple_weight(xs) << '\n';
    }

    return 0;
}
