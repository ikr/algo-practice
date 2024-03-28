#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

#define rep(i, a, b) for (int i = a; i < (b); ++i)

// https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/Zfunc.h
vector<int> Z_with_a_twist(const string &S) {
    vector<int> z(sz(S));
    int l = -1, r = -1;
    rep(i, 1, sz(S)) {
        z[i] = i >= r ? 0 : min(r - i, z[i - l]);
        int diffs = 0;
        while (i + z[i] < sz(S)) {
            if (S[i + z[i]] == S[z[i]]) {
                z[i]++;
            } else if (diffs == 0) {
                z[i]++;
                diffs++;
            } else {
                break;
            }
        }
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}

int solve(const string &xs, const vector<int> &zs) {
    const auto n = sz(xs);
    if (n < 3) return 1;

    auto l = n;
    while (l != 1 && (zs[l / 2] == l / 2)) {
        l /= 2;
    }
    return l;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs;
        cin >> xs;

        const auto zs = Z_with_a_twist(xs);
        cout << solve(xs, zs) << '\n';
    }

    return 0;
}
