#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static constexpr int M = 4;

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
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<ll> xs(n);
    for (auto &x : xs) cin >> x;

    // odd[i][j] is the number of sub-arrays having odd number of elements with
    // bit i set, that end at index j
    vector<vector<ll>> odd(M, vector(n, 0LL));

    vector<vector<ll>> evn(M, vector(n, 0LL));

    for (int i = 0; i < M; ++i) {
        if (xs[0] & (1LL << i)) {
            odd[i][0] = 1;
        } else {
            evn[i][0] = 1;
        }

        for (int j = 1; j < n; ++j) {
            if (xs[j] & (1LL << i)) {
                odd[i][j] = 1 + evn[i][j - 1];
                evn[i][j] = odd[i][j - 1];
            } else {
                odd[i][j] = odd[i][j - 1];
                evn[i][j] = 1 + evn[i][j - 1];
            }
        }
    }

    cerr << odd << '\n' << endl;
    cerr << evn << endl;

    ll ans = -1LL * accumulate(cbegin(xs), cend(xs), 0LL);

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < n; ++j) {
            ans += (1LL << i) * odd[i][j];
        }
    }

    cout << ans << '\n';
    return 0;
}
