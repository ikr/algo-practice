#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using Rows = vector<string>;

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> &lhs, const pair<T, T> &rhs) {
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

template <typename Iter, typename R, typename Binop, typename Unaop>
R ttransform_reduce(Iter first, Iter last, R init, Binop binop, Unaop unaop) {
    return inner_product(first, last, first, init, binop,
                         [&unaop](const auto &x,
                                  __attribute__((unused))
                                  const auto &x_) { return unaop(x); });
}

template <typename T> struct mmax final {
    constexpr T operator()(const T &a, const T &b) const {
        return std::max(a, b);
    }
};

int seq_hash(const string &s) {
    constexpr int sz = 10;
    assert(s.size() == sz);
    return bitset<sz>(s, 0, string::npos, '.', '#').to_ulong();
}

int side_hash(string side) {
    const int direct = seq_hash(side);
    reverse(begin(side), end(side));
    const int flipped = seq_hash(side);
    return min(direct, flipped);
}

string column(const Rows &rows, const int co) {
    const int sz = rows.size();
    string ans(sz, ' ');
    for (int i = 0; i < sz; ++i) ans[i] = rows[i][co];
    return ans;
}

Rows rotate_rows(const Rows &rows) {
    const int sz = rows.size();
    Rows ans(sz, string(sz, ' '));

    for (int i = 0; i < sz; ++i) {
        for (int j = 0; j < sz; ++j) ans[j][sz - 1 - i] = rows[i][j];
    }

    return ans;
}

Rows flip_rows(Rows rows) {
    transform(cbegin(rows), cend(rows), begin(rows), [](string row) {
        reverse(begin(row), end(row));
        return row;
    });

    return rows;
}

vector<Rows> complete_group(const Rows &rows) {
    const auto direct_90 = rotate_rows(rows);
    const auto direct_180 = rotate_rows(direct_90);
    const auto direct_270 = rotate_rows(direct_180);

    const auto flipped = flip_rows(rows);
    const auto flipped_90 = rotate_rows(flipped);
    const auto flipped_180 = rotate_rows(flipped_90);
    const auto flipped_270 = rotate_rows(flipped_180);

    return {rows,    direct_90,  direct_180,  direct_270,
            flipped, flipped_90, flipped_180, flipped_270};
}

struct Tile final {
    Tile(const int id, const Rows &rows) : m_id{id}, m_rows{rows} {}
    Tile() : m_id{0}, m_rows{} {}
    int id() const { return m_id; }
    int printed_size() const { return m_rows.size() - 2; }

    void print_to(Rows &rows, const int ro, const int co) const {
        for (int i = 0; i < printed_size(); ++i) {
            rows[ro + i].replace(co, printed_size(),
                                 m_rows[1 + i].substr(1, printed_size()));
        }
    }

    vector<int> side_hashes() const {
        return {side_hash(m_rows[0]), right_side_hash(), bottom_side_hash(),
                side_hash(column(m_rows, 0))};
    }

    Tile orient_north_west(const multimap<int, Tile> &index) const {
        for (const auto &rows : complete_group(m_rows)) {
            const bool topmost = index.count(side_hash(rows[0])) == 1;
            if (!topmost) continue;

            const bool leftmost = index.count(side_hash(column(rows, 0))) == 1;
            if (!leftmost) continue;

            return {m_id, rows};
        }

        assert(false && "Can't orient NW");
    }

    Tile snap_right(const Tile &left_neigh) const {
        const int sz = m_rows.size();
        const auto side = column(left_neigh.m_rows, sz - 1);

        for (const auto &rows : complete_group(m_rows)) {
            if (side == column(rows, 0)) return {m_id, rows};
        }

        assert(false && "Can't snap right");
    }

    Tile snap_bottom(const Tile &top_neigh) const {
        for (const auto &rows : complete_group(m_rows)) {
            if (top_neigh.m_rows.back() == rows[0]) return {m_id, rows};
        }

        assert(false && "Can't snap bottom");
    }

    int right_side_hash() const {
        return side_hash(column(m_rows, m_rows.size() - 1));
    }

    int bottom_side_hash() const { return side_hash(m_rows.back()); }

  private:
    int m_id;
    Rows m_rows;
};

multimap<int, Tile> gather_index(const vector<Tile> &tiles) {
    multimap<int, Tile> ans;
    for (const auto &t : tiles) {
        for (const auto h : t.side_hashes()) ans.emplace(h, t);
    }
    return ans;
}

Tile suggest_top_left_corner(const vector<Tile> &tiles,
                             const multimap<int, Tile> &index) {
    for (const auto &t : tiles) {
        const auto hs = t.side_hashes();

        const auto neighs = ttransform_reduce(
            cbegin(hs), cend(hs), 0, plus<int>{},
            [&index](const int h) { return index.count(h) - 1; });

        if (neighs == 2) return t;
    }

    assert(false && "Can't suggest top-left");
    return {};
}

Tile another_of(const multimap<int, Tile>::const_iterator first,
                const multimap<int, Tile>::const_iterator last,
                const int excluded_id) {
    for (auto it = first; it != last; ++it) {
        const auto [_, t] = *it;
        if (t.id() != excluded_id) return t;
    }

    assert(false && "Can't determine another of");
    return {};
}

vector<vector<Tile>> stitch_tiles_grid(const vector<Tile> &tiles) {
    const int k = sqrt(tiles.size());
    assert(k * k == tiles.size());

    vector<vector<Tile>> grid(k, vector<Tile>(k));

    const auto index = gather_index(tiles);
    grid[0][0] = suggest_top_left_corner(tiles, index).orient_north_west(index);

    for (int i = 1; i < k; ++i) {
        const auto t0 = grid[0][i - 1];
        const auto [first, last] = index.equal_range(t0.right_side_hash());
        const auto t1 = another_of(first, last, t0.id());
        grid[0][i] = t1.snap_right(t0);
    }

    for (int i = 1; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            const auto t0 = grid[i - 1][j];
            const auto [first, last] = index.equal_range(t0.bottom_side_hash());
            const auto t1 = another_of(first, last, t0.id());
            grid[i][j] = t1.snap_bottom(t0);
        }
    }

    return grid;
}

Rows print_raster(const vector<vector<Tile>> &grid) {
    const int k = grid.size();
    const int d = grid[0][0].printed_size();
    Rows ans(k * d, string(k * d, ' '));

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) grid[i][j].print_to(ans, i * d, j * d);
    }

    return ans;
}

vector<pair<int, int>> monster_path() {
    return {{0, 0}, {1, 1}, {0, 3}, {-1, 1}, {0, 1},  {1, 1}, {0, 3}, {-1, 1},
            {0, 1}, {1, 1}, {0, 3}, {-1, 1}, {-1, 1}, {1, 0}, {0, 1}};
}

int count_monsters(const Rows &rows) {
    const int sz = rows.size();
    assert(sz == static_cast<int>(rows[0].size()));

    const auto is_match = [&](const pair<int, int> p) {
        const auto [ro, co] = p;
        return ro >= 0 && ro < sz && co >= 0 && co < sz && rows[ro][co] == '#';
    };

    int ans = 0;
    for (int ro = 0; ro < sz; ++ro) {
        for (int co = 0; co < sz; ++co) {
            pair<int, int> p{ro, co};
            bool matched = true;

            for (const auto d : monster_path()) {
                p = p + d;
                if (!is_match(p)) {
                    matched = false;
                    break;
                }
            }

            if (matched) ++ans;
        }
    }
    return ans;
}

int count_pounds(const Rows &rows) {
    return ttransform_reduce(
        cbegin(rows), cend(rows), 0, plus<int>{},
        [](const auto &s) { return count(cbegin(s), cend(s), '#'); });
}

int solve(const vector<Tile> &tiles) {
    const auto rasters = complete_group(print_raster(stitch_tiles_grid(tiles)));
    const int m = ttransform_reduce(cbegin(rasters), cend(rasters), 0,
                                    mmax<int>{}, count_monsters);
    return count_pounds(rasters[0]) - m * monster_path().size();
}

int main() {
    vector<Tile> tiles;
    int id = 0;
    Rows rows;

    for (string line; getline(cin, line);) {
        const string header{"Tile "};
        if (line.find(header) == 0) {
            id = stoi(line.substr(header.size(), 4));
            continue;
        }

        if (line == "") {
            tiles.emplace_back(id, rows);
            id = 0;
            rows.clear();
            continue;
        }

        rows.push_back(line);
    }

    cout << solve(tiles) << '\n';
    return 0;
}
