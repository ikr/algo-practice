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
    vector<vector<pii>> row_reflections(sz(grid));
    row_reflections[0] = reflections(grid[0]);
    map<int, int> ds_by_col;
    for (const auto &[co, d] : row_reflections[0]) ds_by_col[co] = d;

    for (int ro = 1; ro < sz(grid); ++ro) {
        row_reflections[ro] = reflections(grid[ro]);
        set<int> cols;

        for (const auto &[co, d] : row_reflections[ro]) {
            if (ds_by_col.contains(co) && ds_by_col[co] != d) {
                ds_by_col.erase(co);
            }
            cols.insert(co);
        }

        for (auto it = cbegin(ds_by_col); it != cend(ds_by_col);) {
            if (!cols.contains(it->first)) {
                it = ds_by_col.erase(it);
            } else {
                ++it;
            }
        }
    }

    return empty(ds_by_col)
               ? pii{-1, -1}
               : pii{cbegin(ds_by_col)->first, cbegin(ds_by_col)->second};
}

pii last_element(const map<int, int> &m) {
    assert(!empty(m));
    return *prev((cend(m)));
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
        auto grid = grid0;

        map<int, int> col_reflections_by_size;
        map<int, int> row_reflections_by_size;

        for (int r = 0; r < sz(grid); ++r) {
            for (int c = 0; c < sz(grid[r]); ++c) {
                grid[r][c] = grid[r][c] == '.' ? '#' : '.';

                const auto rco = common_reflection_col(grid);
                if (rco.first != -1) {
                    col_reflections_by_size[rco.second] = rco.first;
                }

                const auto grid_ = transpose(grid);
                const auto rro = common_reflection_col(grid_);
                if (rro.first != -1) {
                    row_reflections_by_size[rro.second] = rro.first;
                }
            }
        }

        cerr << "column_reflections_by_size: " << col_reflections_by_size
             << endl;
        cerr << "row_reflections_by_size: " << row_reflections_by_size << endl;

        assert(!empty(row_reflections_by_size) ||
               !empty(col_reflections_by_size));

        if (empty(row_reflections_by_size)) {
            result += last_element(col_reflections_by_size).second + 1;
        } else if (empty(col_reflections_by_size)) {
            result += 100 * (last_element(row_reflections_by_size).second + 1);
        } else {
            if (last_element(col_reflections_by_size).first >
                last_element(row_reflections_by_size).first) {
                result += last_element(col_reflections_by_size).second + 1;
            } else {
                result +=
                    100 * (last_element(row_reflections_by_size).second + 1);
            }
        }
    }
    cout << result << '\n';
    return 0;
}
