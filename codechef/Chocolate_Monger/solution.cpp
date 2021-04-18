#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

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

int max_kinds(const int leave, const vi &xs) {
    map<int, int> fs;
    for (const auto x : xs) ++fs[x];

    vector<int> fx;
    fx.reserve(sz(fs));
    for (const auto [_, v] : fs) fx.push_back(v);
    sort(rbegin(fx), rend(fx));

    int i = 0;
    int x = leave;

    while (i < sz(fx)) {
        const int d = min(x, fx[i] - 1);
        x -= d;
        fx[i] -= d;
        ++i;
    }

    const int remains =
        inof(count_if(cbegin(fx), cend(fx), [](const int z) { return z > 0; }));

    return max(0, remains - x);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n, x;
        cin >> n >> x;

        vi as(n);
        for (auto &a : as) cin >> a;

        cout << max_kinds(x, as) << '\n';
    }

    return 0;
}
