#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
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

vector<vector<int>> distances_for(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    vector<vector<int>> D(H, vector(W, INF));
    queue<pii> q;

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] == '1') {
                q.emplace(ro, co);
                D[ro][co] = 0;
            }
        }
    }
    assert(!q.empty());

    while (!q.empty()) {
        const auto [ro, co] = q.front();
        q.pop();

        if (ro && D[ro - 1][co] == INF) {
            D[ro - 1][co] = D[ro][co] + 1;
            q.emplace(ro - 1, co);
        }

        if (ro < H - 1 && D[ro + 1][co] == INF) {
            D[ro + 1][co] = D[ro][co] + 1;
            q.emplace(ro + 1, co);
        }

        if (co && D[ro][co - 1] == INF) {
            D[ro][co - 1] = D[ro][co] + 1;
            q.emplace(ro, co - 1);
        }

        if (co < W - 1 && D[ro][co + 1] == INF) {
            D[ro][co + 1] = D[ro][co] + 1;
            q.emplace(ro, co + 1);
        }
    }

    return D;
}

pii roco_of_max(const vector<vector<int>> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);
    int a{}, b{};

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            if (grid[ro][co] > grid[a][b]) {
                a = ro;
                b = co;
            }
        }
    }

    return {a, b};
}

int overall_delivery_time(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    auto D = distances_for(grid);
    const auto [a, b] = roco_of_max(D);
    if (D[a][b] == 0) return 0;

    int lo = 0;
    int hi = D[a][b];
    for (;;) {
        const auto mid = lo + (hi - lo) / 2;
        auto x_lo = INF, y_lo = INF, x_hi = -INF, y_hi = -INF;

        for (int ro = 0; ro < H; ++ro) {
            for (int co = 0; co < W; ++co) {
                if (D[ro][co] > mid) {
                    const auto x = ro + co;
                    const auto y = ro - co;

                    x_lo = min(x_lo, x);
                    y_lo = min(y_lo, y);
                    x_hi = max(x_hi, x);
                    y_hi = max(y_hi, y);
                }
            }
        }

        const auto fulfilled = [&]() -> bool {
            for (int ro = 0; ro < H; ++ro) {
                for (int co = 0; co < W; ++co) {
                    const auto x = ro + co;
                    const auto y = ro - co;

                    const auto d = max({abs(x - x_hi), abs(x - x_lo),
                                        abs(y - y_hi), abs(y - y_lo)});
                    if (d <= mid) return true;
                }
            }

            return false;
        }();

        if (fulfilled) {
            if (hi == mid) break;
            hi = mid;
        } else {
            if (lo == mid) break;
            lo = mid;
        }
    }

    return hi;
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
