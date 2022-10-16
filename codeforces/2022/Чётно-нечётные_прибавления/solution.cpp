#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<ll> conseq_sums(const vector<int> &A, const vector<pii> &Q) {
    vector<ll> xs0;
    vector<ll> xs1;

    for (const auto x : A) {
        if (x % 2) {
            xs1.push_back(x);
        } else {
            xs0.push_back(x);
        }
    }

    auto s0 = accumulate(cbegin(xs0), cend(xs0), 0LL);
    auto s1 = accumulate(cbegin(xs1), cend(xs1), 0LL);

    ll a0{};
    ll a1{};
    vector<ll> result;
    result.reserve(sz(Q));

    for (const auto &[cmd, x] : Q) {
        if (cmd == 0) {
            a0 += x;

            if (x % 2 != 0) {
                if (xs1.empty()) {
                    swap(xs1, xs0);
                    swap(a1, a0);
                    swap(s1, s0);
                } else {
                    for (const auto y : xs0) {
                        xs1.push_back(y + a0 - a1);
                        s1 += y + a0 - a1;
                    }

                    xs0.clear();
                    a0 = 0LL;
                    s0 = 0LL;
                }
            }
        } else {
            assert(cmd == 1);
            a1 += x;

            if (x % 2 != 0) {
                if (xs0.empty()) {
                    swap(xs1, xs0);
                    swap(a1, a0);
                    swap(s1, s0);
                } else {
                    for (const auto y : xs1) {
                        xs0.push_back(y + a1 - a0);
                        s0 += y + a1 - a0;
                    }

                    xs1.clear();
                    a1 = 0LL;
                    s1 = 0LL;
                }
            }
        }

        result.push_back(s0 + s1 + sz(xs0) * a0 + sz(xs1) * a1);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<int> A(n);
        for (auto &a : A) cin >> a;

        vector<pii> Q(q);
        for (auto &[cmd, x] : Q) cin >> cmd >> x;

        for (const auto s : conseq_sums(A, Q)) {
            cout << s << '\n';
        }
    }

    return 0;
}
