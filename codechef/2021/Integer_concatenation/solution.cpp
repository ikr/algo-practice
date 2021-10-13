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

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> vi digits_reversed(T n) {
    vi ans;

    while (n) {
        ans.push_back(n % 10);
        n /= 10;
    }

    return ans;
}

template <typename T> vi digits(T n) {
    vi ans = digits_reversed(n);
    reverse(begin(ans), end(ans));
    return ans;
}

template <typename T> T number(const vi &ds) {
    if (ds.empty()) return 0;

    T ans = 0;
    T mul = 1;
    for (auto it = ds.crbegin(); it != ds.crend(); ++it) {
        ans += (*it) * mul;
        mul *= static_cast<T>(10);
    }
    return ans;
}

vi concat(vi xs, const vi &ys) {
    xs.insert(cend(xs), cbegin(ys), cend(ys));
    return xs;
}

ll concat(const ll x, const ll y) {
    return number<ll>(concat(digits(x), digits(y)));
}

ll k_nines(const int k) { return number<ll>(vi(k, 9)); }

ll min_prefix_to_be_at_least_A(const int x, const ll A) {
    if (concat(1, x) >= A) return 1;

    ll lo = 1;
    ll hi = [&]() -> ll {
        const int own = sz(digits_reversed(x));
        const int of_a = sz(digits_reversed(A));
        assert(of_a > own);
        return k_nines(of_a - own + 1);
    }();

    assert(concat(hi, x) > A);
}

ll suitable_pairs_num(const vi &xs, const int L, const int R) {
    assert(L <= R);
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        ll L, R;
        cin >> L >> R;

        vi xs(N);
        for (auto &x : xs) cin >> x;
    }

    return 0;
}
