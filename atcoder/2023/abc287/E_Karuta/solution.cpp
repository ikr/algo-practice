#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

namespace kactl {
#define rep(i, a, b) for (int i = a; i < (b); ++i)

using vi = vector<int>;

vi Z(const string &S) {
    vi z(sz(S));
    int l = -1, r = -1;
    rep(i, 1, sz(S)) {
        z[i] = i >= r ? 0 : min(r - i, z[i - l]);
        while (i + z[i] < sz(S) && S[i + z[i]] == S[z[i]]) z[i]++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}
} // namespace kactl

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<string> xs(N);
    for (auto &x : xs) cin >> x;

    vector<int> idx(N, 1);
    string s = "|" + xs[0];

    for (int i = 1; i < N; ++i) {
        s += '|';
        idx[i] = sz(s);
        s += xs[i];
    }

    const auto z = kactl::Z(s);

    vector<int> ans;
    ans.reserve(N);
    for (const auto i : idx) {
        ans.push_back(z[i]);
    }

    for (const auto a : ans) {
        cout << a << '\n';
    }
    return 0;
}
