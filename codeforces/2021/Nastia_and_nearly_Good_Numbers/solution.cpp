#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Tri = tuple<ll, ll, ll>;

optional<Tri> solution(const ll a, const ll b) {
    if (b == 1) return nullopt;
    return Tri{b * a, (b + 1LL) * a, (2LL * b + 1LL) * a};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        ll a, b;
        cin >> a >> b;

        const auto ans = solution(a, b);
        if (!ans) {
            cout << "NO\n";
        } else {
            const auto [x, y, z] = *ans;
            cout << "YES\n" << x << ' ' << y << ' ' << z << '\n';
        }
    }

    return 0;
}
