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

pii solution(const vi &xs) {
    array<int, 30> fs{};

    for (const auto &x : xs) {
        for (int i = 0; i < sz(fs); ++i) {
            if (x & (1 << i)) ++fs[i];
        }
    }

    int v = 0;

    for (int i = 0; i < sz(fs); ++i) {
        const ll having = fs[i];
        const ll missing = sz(xs) - fs[i];
        assert(having >= 0 && missing >= 0);

        const ll s1 = llof(1 << i) * missing;
        const ll s0 = llof(1 << i) * having;
        if (s1 < s0) {
            v |= (1 << i);
        }
    }

    int s = 0;

    for (const auto x : xs) {
        s |= (x ^ v);
    }

    return { v, s };
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(n);
        for (auto &x : xs) cin >> x;

        const auto [x, s] = solution(xs);
        cout << x << ' ' << s << '\n';
    }

    return 0;
}
