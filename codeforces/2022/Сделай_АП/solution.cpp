#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const ll a, const ll b, const ll c) {
    { // a * m
        const auto d = c - b;
        if ((b - d) % a == 0LL && (b - d) / a > 0) return true;
    }

    if ((c - a) % 2LL == 0) { // b * m
        const auto d = (c - a) / 2LL;
        if ((a + d) % b == 0LL && (a + d) / b > 0) return true;
    }

    { // c * m
        const auto d = b - a;
        if ((b + d) % c == 0LL && (b + d) / c > 0) return true;
    }

    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int a, b, c;
        cin >> a >> b >> c;

        cout << (is_possible(a, b, c) ? "YES" : "NO") << '\n';
    }

    return 0;
}
