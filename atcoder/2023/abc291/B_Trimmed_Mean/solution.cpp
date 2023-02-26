#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(6) << fixed;

    int N;
    cin >> N;

    vector<int> xs(5 * N);
    for (auto &x : xs) cin >> x;

    sort(begin(xs), end(xs));
    xs.erase(cbegin(xs) + 4 * N, cend(xs));
    xs.erase(cbegin(xs), cbegin(xs) + N);

    const double s = accumulate(cbegin(xs), cend(xs), 0);
    cout << (s / (3.0 * N)) << '\n';
    return 0;
}
