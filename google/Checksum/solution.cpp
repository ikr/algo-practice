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

using Coord = complex<int>;
constexpr int row(const Coord coord) { return coord.real(); }
constexpr int col(const Coord coord) { return coord.imag(); }

struct q_less final {
    bool operator()(const pair<int, Coord> &a,
                    const pair<int, Coord> &b) const {
        return pair{a.first, pair{row(a.second), col(a.second)}} <
               pair{b.first, pair{row(b.second), col(b.second)}};
    }
};

using Queue =
    priority_queue<pair<int, Coord>, vector<pair<int, Coord>>, q_less>;

vi missing_num_by_row(const vvi &src) {
    vi ans(sz(src), 0);

    for (int ro = 0; ro < sz(src); ++ro) {
        for (int co = 0; co < sz(src); ++co) {
            if (src[ro][co] == -1) ++ans[ro];
        }
    }

    return ans;
}

vi missing_num_by_col(const vvi &src) {
    vi ans(sz(src), 0);

    for (int ro = 0; ro < sz(src); ++ro) {
        for (int co = 0; co < sz(src); ++co) {
            if (src[ro][co] == -1) ++ans[co];
        }
    }

    return ans;
}

Queue initial_queue(const vvi &costs) {
    Queue ans;

    for (int ro = 0; ro < sz(costs); ++ro) {
        for (int co = 0; co < sz(costs); ++co) {
            ans.emplace(-costs[ro][co], Coord{ro, co});
        }
    }

    return ans;
}

int solve(const vvi &src, const vvi &costs, const vi &rs, const vi &cs) {
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;

        vvi src(n, vi(n, 0));
        for (auto &line : src) {
            for (auto &cell : line) cin >> cell;
        }

        vvi costs(n, vi(n, 0));
        for (auto &line : costs) {
            for (auto &cell : line) cin >> cell;
        }

        vi rs(n, 0);
        for (auto &c : rs) cin >> c;

        vi cs(n, 0);
        for (auto &c : cs) cin >> c;

        cout << "Case #" << i << ": " << solve(src, costs, rs, cs) << '\n';
    }

    return 0;
}
