#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_teams(const vector<int> &xs) {
    const auto n = sz(xs);
    int result{};
    for (int i = 0; i < n - 2;) {
        const auto a = xs[i];
        const auto b = xs[i + 1];
        const auto c = xs[i + 2];

        if (b - a <= 1 && c - b <= 1 && c - a <= 1) {
            ++result;
            i += 3;
        } else {
            ++i;
        }
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;
    sort(begin(xs), end(xs));

    cout << max_teams(xs) << '\n';
    return 0;
}
