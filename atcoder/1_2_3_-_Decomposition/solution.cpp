#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
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

static constexpr int K_MAX = 5;

int min_k(const ll n) {
    const auto xs = digits_reversed(n);

    // ok[i][k][c] is true iﬀ it is possible to produce a carry c at digit i
    // after summing up k 123-numbers

    vector<vector<vector<bool>>> ok(
        sz(xs), vector(K_MAX + 1, vector(K_MAX + 1, false)));

    for (int k = 1; k <= K_MAX; ++k) {
        for (int v = k; v <= 3 * k; ++v) {
            if (v % 10 == xs[0]) {
                ok[0][k][v / 10] = true;
            }
        }
    }

    for (int i = 1; i < sz(xs); ++i) {
        for (int k = 1; k <= K_MAX; ++k) {
            for (int v = k; v <= 3 * k; ++v) {
                for (int c = 0; c <= K_MAX; ++c) {
                    if (!ok[i - 1][k][c]) continue;
                    if ((v + c) % 10 != xs[i]) continue;
                    ok[i][k][(v + c) / 10] = true;
                }
            }
        }
    }

    cerr << ok[0] << endl;

    for (int k = 1; k <= K_MAX; ++k) {
        if (ok.back()[k][0]) return k;
    }

    assert(false);
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;

        cout << min_k(n) << '\n';
    }

    return 0;
}
