#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static constexpr ll Inf = 1e12;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static vector<vector<ll>> M(101);

void precompute() {
    for (ll m = 2; m < sz(M); ++m) {
        const ll base = m;
        M[m].push_back(base);

        while (M[m].back() < Inf) {
            M[m].push_back(M[m].back() * base);
        }
    }
}

ll num_ways(const ll m, const vector<ll> &A, const vector<ll> &B) {
    const ll n = sz(A);
    if (m == 1) return n * n;

    map<ll, int> bfq;
    for (const auto b : B) ++bfq[b];

    ll result{};
    for (const auto target : M[m]) {
        for (const auto a : A) {
            cerr << "target:" << target << " a:" << a << endl;
            const auto b = target - a;
            const auto it = bfq.find(b);
            if (it != cend(bfq)) {
                result += it->second;
                cerr << "found:" << it->second << endl;
            } else {
                cerr << "not found" << endl;
            }
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    precompute();

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<ll> A(n);
        for (auto &a : A) cin >> a;

        vector<ll> B(n);
        for (auto &b : B) cin >> b;

        cout << num_ways(m, A, B) << '\n';
    }

    return 0;
}
