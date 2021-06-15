#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

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

string column(const vector<string> &grid, const int j) {
    string ans(sz(grid), ' ');
    for (int i = 0; i < sz(grid); ++i) ans[i] = grid[i][j];
    return ans;
}

pair<int, vi> enumerate_marks(const vector<string> &grid) {
    const int W = sz(grid[0]);
    map<string, int> idx;
    int curr = 0;

    vi xs(W, 0);

    for (int j = 0; j < W; ++j) {
        const auto c = column(grid, j);

        if (idx.count(c)) {
            xs[j] = idx.at(c);
            continue;
        }

        idx[c] = ++curr;
        xs[j] = curr;
    }

    return {curr, xs};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n, l;
        cin >> n >> l;

        vector<string> grid(n);
        for (auto &row : grid) cin >> row;

        const auto [k, xs] = enumerate_marks(grid);
        cout << k << '\n' << xs << '\n';
    }

    return 0;
}
