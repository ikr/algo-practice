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
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

int subshapes_num(const int x, const int y) {
    assert(x >= 2 && y >= 2);
    int ans = 0;

    if (y >= 4) ans += min(x, y / 2) - 1;
    if (x >= 4) ans += min(y, x / 2) - 1;

    return ans;
}

ll solve(const vvi &grid) {
    const int h = sz(grid);
    const int w = sz(grid[0]);
    ll ans = 0;

    {
        vvi horz(h, vi(w, 0));
        vvi vert(h, vi(w, 0));

        for (int ro = 0; ro < h; ++ro) {
            for (int co = 0; co < w; ++co) {
                if (ro > 0) {
                    vert[ro][co] = grid[ro][co] ? (vert[ro - 1][co] + 1) : 0;
                } else {
                    vert[ro][co] = grid[ro][co];
                }

                if (co > 0) {
                    horz[ro][co] = grid[ro][co] ? (horz[ro][co - 1] + 1) : 0;
                } else {
                    horz[ro][co] = grid[ro][co];
                }

                if (vert[ro][co] >= 2 && horz[ro][co] >= 2) {
                    ans += subshapes_num(horz[ro][co], vert[ro][co]);
                }
            }
        }
    }

    {
        vvi horz(h, vi(w, 0));
        vvi vert(h, vi(w, 0));

        for (int ro = 0; ro < h; ++ro) {
            for (int co = w - 1; co >= 0; --co) {
                if (ro > 0) {
                    vert[ro][co] = grid[ro][co] ? (vert[ro - 1][co] + 1) : 0;
                } else {
                    vert[ro][co] = grid[ro][co];
                }

                if (co < w - 1) {
                    horz[ro][co] = grid[ro][co] ? (horz[ro][co + 1] + 1) : 0;
                } else {
                    horz[ro][co] = grid[ro][co];
                }

                if (vert[ro][co] >= 2 && horz[ro][co] >= 2) {
                    ans += subshapes_num(horz[ro][co], vert[ro][co]);
                }
            }
        }
    }

    {
        vvi horz(h, vi(w, 0));
        vvi vert(h, vi(w, 0));

        for (int ro = h - 1; ro >= 0; --ro) {
            for (int co = w - 1; co >= 0; --co) {
                if (ro < h - 1) {
                    vert[ro][co] = grid[ro][co] ? (vert[ro + 1][co] + 1) : 0;
                } else {
                    vert[ro][co] = grid[ro][co];
                }

                if (co < w - 1) {
                    horz[ro][co] = grid[ro][co] ? (horz[ro][co + 1] + 1) : 0;
                } else {
                    horz[ro][co] = grid[ro][co];
                }

                if (vert[ro][co] >= 2 && horz[ro][co] >= 2) {
                    ans += subshapes_num(horz[ro][co], vert[ro][co]);
                }
            }
        }
    }

    {
        vvi horz(h, vi(w, 0));
        vvi vert(h, vi(w, 0));

        for (int ro = h - 1; ro >= 0; --ro) {
            for (int co = 0; co < w; ++co) {
                if (ro < h - 1) {
                    vert[ro][co] = grid[ro][co] ? (vert[ro + 1][co] + 1) : 0;
                } else {
                    vert[ro][co] = grid[ro][co];
                }

                if (co > 0) {
                    horz[ro][co] = grid[ro][co] ? (horz[ro][co - 1] + 1) : 0;
                } else {
                    horz[ro][co] = grid[ro][co];
                }

                if (vert[ro][co] >= 2 && horz[ro][co] >= 2) {
                    ans += subshapes_num(horz[ro][co], vert[ro][co]);
                }
            }
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int h, w;
        cin >> h >> w;

        vvi grid(h, vi(w));
        for (auto &line : grid) {
            for (auto &cell : line) cin >> cell;
        }

        cout << "Case #" << i << ": " << solve(grid) << '\n';
    }

    return 0;
}
