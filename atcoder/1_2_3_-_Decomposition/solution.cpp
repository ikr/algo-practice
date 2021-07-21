#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

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

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<pair<bool, bool>>>
printable(const vector<vector<vector<bool>>> &in) {
    vector<vector<pair<bool, bool>>> ans(sz(in),
                                         vector(sz(in[0]), pair{false, false}));

    for (int ro = 0; ro < sz(in); ++ro) {
        for (int co = 0; co < sz(in[ro]); ++co) {
            ans[ro][co] = pair{in[ro][co][0], in[ro][co][1]};
        }
    }

    return ans;
}

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
    // after summing up exactly k 123-numbers; note that not all of those k
    // 123-numbers must contribute directly to the digit at index i: some may be
    // shorter
    vector<vector<vector<bool>>> ok(sz(xs),
                                    vector(K_MAX + 1, vector(2, false)));

    for (int k = 1; k <= K_MAX; ++k) {
        for (int v = k; v <= 3 * k; ++v) {
            if (v % 10 == xs[0]) {
                ok[0][k][v / 10] = true;
            }
        }
    }

    for (int i = 1; i < sz(xs); ++i) {
        // May be it's possible to only utilize the carry from the previous
        // digit, and therefore have zero 123-numbers contributing directly
        if (xs[i] <= 1) {
            for (int k = 1; k <= K_MAX; ++k) {
                ok[i][k][0] = ok[i][k][0] || ok[i - 1][k][xs[i]];
            }
        }

        for (int k0 = 1; k0 <= K_MAX; ++k0) {
            for (int v = k0; v <= 3 * k0; ++v) {
                for (int k = k0; k <= K_MAX; ++k) {
                    for (int c = 0; c <= 1; ++c) {
                        if (!ok[i - 1][k][c]) continue;

                        if ((v + c) % 10 == xs[i]) {
                            ok[i][k0][(v + c) / 10] = true;
                        }
                    }
                }
            }
        }
    }

    cerr << printable(ok) << endl;

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
