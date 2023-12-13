#include <bits/stdc++.h>
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

ostream &operator<<(ostream &os, const vector<string> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << '{';
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '(' << i->first << ' ' << i->second << ')';
    }
    os << '}';
    return os;
}

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> transpose(const vector<string> &m) {
    const auto H = sz(m[0]);
    const auto W = sz(m);

    vector<string> ans(H, string(W, ' '));
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            ans[ro][co] = m[co][ro];
        }
    }
    return ans;
}

bool is_palindrome(const string &xs) {
    auto ys = xs;
    ranges::reverse(ys);
    return xs == ys;
}

bool are_columns_mirrored(const vector<string> &grid, const int c0,
                          const int d0) {
    const auto lc = c0 - d0 + 1;
    const auto rc = c0 + d0;
    if (lc < 0 || rc >= sz(grid[0])) return false;
    if (lc != 0 && rc != sz(grid[0]) - 1) return false;

    return ranges::all_of(grid, [&](const string &row) {
        return is_palindrome(row.substr(lc, 2 * d0));
    });
}

pii reflection_col(const vector<string> &grid) {
    const auto W = sz(grid[0]);
    for (int d = W / 2 + 1; d >= 1; --d) {
        for (int c = 0; c < W; ++c) {
            if (are_columns_mirrored(grid, c, d)) return {c, d};
        }
    }
    return {-1, -1};
}

pii last_element(const map<int, int> &m) {
    assert(!empty(m));
    return *prev((cend(m)));
}

int digest(const pii rc, const pii rr) {
    if (rc.first == -1 && rr.first == -1) return 0;
    if (rr.first == -1) return (rc.first + 1);
    if (rc.first == -1) return 100 * (rr.first + 1);
    return rc.second > rr.second ? (rc.first + 1) : (100 * (rr.first + 1));
}

int main() {
    vector<vector<string>> grids(1);

    for (string line; getline(cin, line);) {
        if (empty(line)) {
            grids.emplace_back();
        } else {
            grids.back().push_back(line);
        }
    }

    int result{};

    for (const auto &grid0 : grids) {
        const auto rc0 = reflection_col(grid0);
        const auto rr0 = reflection_col(transpose(grid0));
        cerr << "\nGrid:\n" << grid0 << endl;
        cerr << "Was: " << rc0 << ' ' << rr0 << " digest:" << digest(rc0, rr0)
             << endl;

        auto grid = grid0;

        const auto cur = [&]() -> int {
            for (int r = 0; r < sz(grid); ++r) {
                for (int c = 0; c < sz(grid[r]); ++c) {
                    grid[r][c] = ((grid[r][c] == '.') ? '#' : '.');
                    auto rc = reflection_col(grid);
                    auto rr = reflection_col(transpose(grid));
                    grid[r][c] = ((grid[r][c] == '.') ? '#' : '.');

                    if (rc.first != -1 || rr.first != -1) {
                        cerr << "Found: " << rc << ' ' << rr
                             << " digest:" << digest(rc, rr) << endl;
                    }

                    if (rc == rc0) rc = pii{-1, -1};
                    if (rr == rr0) rr = pii{-1, -1};

                    if (rc.first != -1 || rr.first != -1) {
                        return digest(rc, rr);
                    }
                }
            }
            // assert(false && "Found nothing");
            cerr << "Found nothing :(" << endl;
            return digest(rc0, rr0);
        }();

        result += cur;
    }
    cout << result << '\n';
    return 0;
}
