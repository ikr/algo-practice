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

static constexpr int LIM = (1 << 24);

constexpr int mlog2(const unsigned int x) {
    return inof(8U * sizeof(unsigned int) - __builtin_clz(x) - 1U);
}

constexpr int bound_not(const int x) {
    if (!x) return 1;
    return ((1 << (mlog2(x) + 1)) - 1) & (~x);
}

int solve(const string &s, const string &e) {
    const int si = inof(bitset<8>(s).to_ulong());
    const int ei = inof(bitset<8>(e).to_ulong());
    if (si == ei) return 0;

    vi ds(LIM, -1);
    ds[si] = 0;

    queue<int> q;
    q.push(si);

    while (!q.empty()) {
        const int u = q.front();
        q.pop();

        if (u * 2 == ei || bound_not(u) == ei) return ds[u] + 1;

        if (u * 2 < LIM && ds[u * 2] == -1) {
            ds[u * 2] = ds[u] + 1;
            q.push(u * 2);
        }

        const int v = bound_not(u);
        assert(v < LIM);
        if (ds[v] == -1) {
            ds[v] = ds[u] + 1;
            q.push(v);
        }
    }

    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        string s, e;
        cin >> s >> e;

        const auto ans = solve(s, e);
        cout << "Case #" << i << ": "
             << (ans == -1 ? "IMPOSSIBLE" : to_string(ans)) << '\n';
    }

    return 0;
}
