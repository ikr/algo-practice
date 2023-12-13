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

void print_grid(const vector<string> &grid) {
    for (const auto &row : grid) cerr << row << endl;
    cerr << endl;
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

int reflection_size(const string &xs, const int i0) {
    const auto in_bounds = [&](const int i) { return 0 <= i && i < sz(xs); };

    int result{};
    int l = i0, r = i0 + 1;
    while (in_bounds(l) && in_bounds(r) && xs[l] == xs[r]) {
        result++;
        --l;
        ++r;
    }
    return result;
}

vector<pii> reflections(const string &xs) {
    vector<pii> ans;
    for (int i = 0; i < sz(xs); ++i) {
        const auto rs = reflection_size(xs, i);
        if (rs) ans.emplace_back(i, rs);
    }
    return ans;
}

pii common_reflection_col(const vector<string> &grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    vector<vector<pii>> rs(sz(grid));
    for (int ro = 0; ro < H; ++ro) {
        rs[ro] = reflections(grid[ro]);
    }

    cerr << "grid:" << endl;
    print_grid(grid);
    cerr << "reflections: \n" << rs << endl;

    const auto common_co = [&]() -> int {
        for (int co = 0; co < W; ++co) {
            if (ranges::all_of(rs, [&](const auto &row) {
                    return ranges::any_of(
                        row, [&](const auto &p) { return p.first == co; });
                })) {
                return co;
            }
        }
        return -1;
    }();

    if (common_co == -1) return {-1, -1};

    int d{};
    for (const auto &row : rs) {
        for (const auto &[co, s] : row) {
            d = max(d, s);
        }
    }

    return {common_co, d};
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

    for (const auto &grid : grids) {
        const auto rco = common_reflection_col(grid);
        const auto grid_ = transpose(grid);
        const auto rro = common_reflection_col(grid_);
        cerr << rco << ' ' << rro << endl;

        assert(rco.first != -1 || rro.first != -1);

        if (rco.second > rro.second) {
            result += (rco.first + 1);
        } else {
            result += 100 * (rro.first + 1);
        }
    }
    cout << result << '\n';
    return 0;
}
