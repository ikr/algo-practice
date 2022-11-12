#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int INF = 1'000'000'000;
static constexpr int WIN = 0;
static constexpr int TIE = 1;
static constexpr int LOS = 2;

int max_score(vector<int> xs, vector<int> ys) {
    sort(begin(xs), end(xs));
    sort(begin(ys), end(ys));

    const auto hi_x_idx = [&xs](const int i0, const int y) -> optional<int> {
        const auto it = upper_bound(cbegin(xs) + i0, cend(xs), y);
        if (it == cend(xs)) return nullopt;
        return inof(distance(cbegin(xs), it));
    };

    const auto eq_x_idx = [&xs](const int i0, const int y) -> optional<int> {
        const auto it = lower_bound(cbegin(xs) + i0, cend(xs), y);
        if (it == cend(xs) || *it != y) return nullopt;
        return inof(distance(cbegin(xs), it));
    };

    const auto lo_x_idx = [&xs](const int i0, const int y) -> optional<int> {
        if (xs.empty()) return nullopt;
        const auto it = lower_bound(cbegin(xs) + i0, cend(xs), y);
        if (it == cbegin(xs)) return nullopt;

        const auto jt = lower_bound(cbegin(xs) + i0, cend(xs), *prev(it));
        if (jt == cend(xs) || *jt != *prev(it)) return nullopt;

        return inof(distance(cbegin(xs), jt));
    };

    vector<array<optional<pii>, 3>> D(sz(ys));
    for (auto &row : D) row.fill(nullopt);

    if (hi_x_idx(0, ys[0])) {
        D[0][WIN] = pii{1, *hi_x_idx(0, ys[0])};
    }

    if (eq_x_idx(0, ys[0])) {
        D[0][TIE] = pii{0, *eq_x_idx(0, ys[0])};
    }

    if (lo_x_idx(0, ys[0])) {
        D[0][LOS] = pii{-1, *lo_x_idx(0, ys[0])};
    }

    for (int i = 1; i < sz(D); ++i) {
        if (D[i - 1][WIN]) {
            const auto [s0, i0] = *D[i - 1][WIN];
        }
    }

    int result = -INF;
    if (D.back()[WIN]) result += D.back()[WIN]->first;
    if (D.back()[TIE]) result += D.back()[TIE]->first;
    if (D.back()[LOS]) result += D.back()[LOS]->first;
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    vector<int> ys(n);
    for (auto &y : ys) cin >> y;

    cout << max_score(move(xs), move(ys)) << '\n';
    return 0;
}
