#include <bits/stdc++.h>
using namespace std;
using ll = long long;

static constexpr int SZ = 10;

template <typename Iter, typename R, typename Binop, typename Unaop>
R ttransform_reduce(Iter first, Iter last, R init, Binop binop, Unaop unaop) {
    R ans = init;

    for (auto it = first; it != last; ++it) {
        ans = binop(ans, unaop(*it));
    }

    return ans;
}

int seq_hash(const string &s) {
    return bitset<SZ>(s, 0, string::npos, '.', '#').to_ulong();
}

int side_hash(string side) {
    int direct = seq_hash(side);
    reverse(begin(side), end(side));
    int flipped = seq_hash(side);
    return min(direct, flipped);
}

struct Tile final {
    Tile(const int id, const vector<string> &rows) : m_id{id}, m_rows{rows} {}
    Tile() : m_id{0}, m_rows{} {}
    int id() const { return m_id; }

    vector<int> side_hashes() const {
        return {side_hash(m_rows[0]), side_hash(column(SZ - 1)),
                side_hash(m_rows[SZ - 1]), side_hash(column(0))};
    }

  private:
    string column(const int co) const {
        string ans(SZ, ' ');
        for (int i = 0; i < SZ; ++i) {
            ans[i] = m_rows[i][co];
        }
        return ans;
    }

    int m_id;
    vector<string> m_rows;
};

multimap<int, Tile> gather_index(const vector<Tile> &tiles) {
    multimap<int, Tile> ans;

    for (const auto &t : tiles) {
        for (const auto h : t.side_hashes()) {
            ans.emplace(h, t);
        }
    }

    return ans;
}

ll solve(const vector<Tile> &tiles) {
    const auto index = gather_index(tiles);

    ll ans = 1;
    for (const auto &t : tiles) {
        const auto hs = t.side_hashes();

        const auto neighs = ttransform_reduce(
            cbegin(hs), cend(hs), 0, plus<int>{},
            [&index](const int h) { return index.count(h) - 1; });

        if (neighs == 2) ans *= t.id();
    }

    return ans;
}

int main() {
    vector<Tile> tiles;
    int id = 0;
    vector<string> rows;

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
