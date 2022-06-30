#include <cassert>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

using pii = pair<int, int>;
static constexpr int INF = 1e9;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

pair<vector<pii>, vector<pii>> spaces_and_offices(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    vector<pii> spaces;
    vector<pii> offices;

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] == '1') {
                offices.emplace_back(ro, co);
            } else {
                spaces.emplace_back(ro, co);
            }
        }
    }

    return {spaces, offices};
}

constexpr int manh(const pii ab, const pii xy) {
    return abs(ab.first - xy.first) + abs(ab.second - xy.second);
}

int min_manh_dist(const vector<pii> &dests, const pii src) {
    int result = INF;
    for (const auto &t : dests) {
        result = min(result, manh(src, t));
    }
    return result;
}

pair<multiset<int>, vector<vector<int>>>
delivery_times_for(const int H, const int W, const vector<pii> &spaces,
                   const vector<pii> &offices) {
    multiset<int> T;
    vector<vector<int>> D(H, vector(W, 0));

    for (const auto &sp : spaces) {
        const auto d = min_manh_dist(offices, sp);
        D[sp.first][sp.second] = d;
        T.insert(d);
    }
    return {T, D};
}

int overall_delivery_time(const vector<string> &grid) {
    const auto [spaces, offices] = spaces_and_offices(grid);
    if (sz(spaces) < 2) return 0;

    const auto [T0, D] =
        delivery_times_for(sz(grid), sz(grid[0]), spaces, offices);

    int result = T0.empty() ? INF : *crbegin(T0);

    for (const auto &o : spaces) {
        auto T = T0;
        T.erase(T.find(D[o.first][o.second]));

        for (const auto &sp : spaces) {
            if (sp == o) continue;
            const auto d = manh(sp, o);
            if (d >= D[sp.first][sp.second]) continue;

            T.erase(T.find(D[sp.first][sp.second]));
            T.insert(d);
        }

        result = min(result, *crbegin(T));
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
