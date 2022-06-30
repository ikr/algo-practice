#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

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

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<set<pii>, set<pii>> partition_rotated(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    set<pii> spaces;
    set<pii> offices;

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            const auto x = ro - co;
            const auto y = ro + co;

            if (grid[ro][co] == '1') {
                offices.emplace(x, y);
            } else {
                spaces.emplace(x, y);
            }
        }
    }

    return {spaces, offices};
}

template <typename T> constexpr pair<T, T> flip(const pair<T, T> &x) {
    return {x.second, x.first};
}

struct FlippedLess final {
    bool operator()(const pii &a, const pii &b) const {
        return flip(a) < flip(b);
    }
};

constexpr int cheb(const pii ab, const pii xy) {
    const auto [a, b] = ab;
    const auto [x, y] = xy;
    return max(abs(a - x), abs(b - y));
}

template <typename T> pii nearest_by_cheb(const T &dests, const pii src) {
    auto it = dests.lower_bound(src);
    if (it == cend(dests)) it = prev(cend(dests));

    const auto jt = it == cbegin(dests) ? it : prev(it);

    return cheb(src, *jt) < cheb(src, *it) ? (*jt) : (*it);
}

int best_delivery_time(const set<pii> &offices,
                       const set<pii, FlippedLess> &offices_, const pii src) {
    const auto ab = nearest_by_cheb(offices, src);
    const auto ab_ = nearest_by_cheb(offices_, src);
    return min(cheb(src, ab), cheb(src, ab_));
}

int overall_delivery_time(const vector<string> &grid) {
    auto [spaces, offices] = partition_rotated(grid);
    set<pii, FlippedLess> offices_(cbegin(offices), cend(offices));

    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    vector<vector<int>> D(H, vector(W, 0));

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] == '1') continue;
            const auto x = ro - co;
            const auto y = ro + co;

            D[ro][co] = best_delivery_time(offices, offices_, {x, y});
        }
    }
    cerr << D << endl;

    int result{};
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int H, W;
        cin >> H >> W;

        vector<string> grid(H, string(W, ' '));
        for (auto &row : grid) cin >> row;

        cout << "Case #" << i << ": " << overall_delivery_time(grid) << '\n';
    }

    return 0;
}
