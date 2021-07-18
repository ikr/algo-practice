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

vi digits_reversed(ll n) {
    vi ans;

    while (n) {
        ans.push_back(inof(n % 10LL));
        n /= 10;
    }

    return ans;
}

vi digits(const ll n) {
    vi ans = digits_reversed(n);
    reverse(begin(ans), end(ans));
    return ans;
}

ll number(const vi &ds) {
    if (ds.empty()) return 0;

    long long ans = 0;
    long long mul = 1;
    for (auto it = ds.crbegin(); it != ds.crend(); ++it) {
        ans += (*it) * mul;
        mul *= 10LL;
    }
    return ans;
}

vi insert_at(vi ds, const int i, const int d) {
    ds.insert(next(cbegin(ds), i), d);
    return ds;
}

void append_next_generation(vll &xs) {
    xs.reserve(sz(xs) * 6);

    const int n = sz(xs);

    for (int k = 0; k < n; ++k) {
        const auto x = xs[k];
        const auto ds = digits(x);

        for (int d = 1; d <= 3; ++d) {
            for (int i = 0; i <= sz(ds); ++i) {
                xs.push_back(number(insert_at(ds, i, d)));
            }
        }
    }
}

vll all_basis() {
    vll ans{1, 2, 3};

    for (int i = 0; i < 7; ++i) {
        append_next_generation(ans);
    }

    sort(begin(ans), end(ans));
    cerr << "hi: " << ans.back() << endl;
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const auto bs = all_basis();

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
    }

    return 0;
}
