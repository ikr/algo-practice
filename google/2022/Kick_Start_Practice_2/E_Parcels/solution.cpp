#include <cassert>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

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
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename T, typename P>
ostream &operator<<(ostream &os, const set<T, P> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
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
            // const auto x = ro - co;
            // const auto y = ro + co;

            if (grid[ro][co] == '1') {
                offices.emplace(ro, co);
            } else {
                spaces.emplace(ro, co);
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

constexpr int manh(const pii ab, const pii xy) {
    const auto [a, b] = ab;
    const auto [x, y] = xy;
    return abs(a - x) + abs(b - y);
}

template <typename T> pii nearest_by_cheb(const T &dests, const pii src) {
    auto it = dests.lower_bound(src);
    if (it == cend(dests)) it = prev(cend(dests));

    const auto jt = it == cbegin(dests) ? it : prev(it);

    return cheb(src, *jt) < cheb(src, *it) ? (*jt) : (*it);
}

static constexpr int INF = 1e9;

int best_delivery_time(const set<pii> &offices,
                       const set<pii, FlippedLess> &offices_, const pii src) {
    const auto ab = nearest_by_cheb(offices, {src.first, -INF});
    const auto ab_ = nearest_by_cheb(offices_, {-INF, src.second});
    return min(cheb(src, ab), cheb(src, ab_));
}

int overall_delivery_time(const vector<string> &grid) {
    auto [spaces, offices] = partition_rotated(grid);
    if (sz(spaces) < 2) return 0;
    set<pii, FlippedLess> offices_(cbegin(offices), cend(offices));

    int result = INF;
    const vector<pii> opts(cbegin(spaces), cend(spaces));

    for (const auto &o : opts) {
        spaces.erase(o);
        assert(!spaces.empty());
        offices.insert(o);
        offices_.insert(o);

        int cur{};
        for (const auto &sp : spaces) {
            // cur = max(cur, best_delivery_time(offices, offices_, sp));

            int best = INF;
            for (const auto &of : offices) {
                best = min(best, manh(sp, of));
            }
            cur = max(cur, best);
        }
        result = min(result, cur);

        spaces.insert(o);
        offices.erase(o);
        offices_.erase(o);
    }

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
