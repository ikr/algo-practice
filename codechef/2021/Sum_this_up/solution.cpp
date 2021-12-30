#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

ll expected_v(const vll &xs) {
    const auto s = doof(accumulate(cbegin(xs), cend(xs), 0LL, plus<ll>{}));
    return llof(abs(s / doof(sz(xs))));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vll xs(n, 0);
        for (auto &x : xs) cin >> x;

        cout << expected_v(xs) << '\n';
    }

    return 0;
}
