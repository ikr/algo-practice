#include <bits/stdc++.h>
using namespace std;

using Freq = array<int, 26>;
using pii = pair<int, int>;

static constexpr Freq Empty{};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> transpose(const vector<string> &m) {
    const auto H = sz(m[0]);
    const auto W = sz(m);

    vector<string> ans(H, string(W, '.'));
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            ans[ro][co] = m[co][ro];
        }
    }
    return ans;
}

Freq frequences(const string &xs) {
    Freq result{};
    for (const auto x : xs) {
        ++result[x - 'a'];
    }
    return result;
}

constexpr bool is_non_zero(const int x) { return !!x; }

constexpr optional<int> markable_value(const Freq &xs) {
    if (ranges::count_if(xs, is_non_zero) != 1) {
        return nullopt;
    }

    const auto it = ranges::find_if(xs, is_non_zero);
    assert(it != cend(xs) && *it > 0);
    return *it == 1 ? nullopt : optional{it - cbegin(xs)};
}

vector<pii> indices_to_mark(const vector<Freq> &xss) {
    vector<pii> result;
    for (auto i = sz(xss) - 1; i >= 0; --i) {
        const auto mbx = markable_value(xss[i]);
        if (mbx) result.emplace_back(i, *mbx);
    }
    return result;
}

constexpr bool contains_index(const vector<pii> &ixs, const int i) {
    return ranges::any_of(ixs, [i](const auto &p) { return p.first == i; });
}

int cookies_num_remaining(const vector<string> &grid) {
    vector<Freq> rows(size(grid));
    ranges::transform(grid, begin(rows), frequences);

    assert(!empty(grid));
    vector<Freq> cols(size(grid[0]));
    ranges::transform(transpose(grid), begin(cols), frequences);

    auto mrows = indices_to_mark(rows);
    auto mcols = indices_to_mark(cols);

    while (!mrows.empty() || !mcols.empty()) {
        vector<pii> mrows_;
        vector<pii> mcols_;

        for (const auto &[iro, x] : mrows) {
            for (int ico = 0; ico < sz(cols); ++ico) {
                if (cols[ico] == Empty || contains_index(mcols, ico)) continue;
                --cols[ico][x];
                if (cols[ico] == Empty) mcols_.emplace_back(ico, x);
            }
        }

        for (const auto &[ico, x] : mcols) {
            for (int iro = 0; iro < sz(rows); ++iro) {
                if (rows[iro] == Empty) continue;
                --rows[iro][x];
                if (rows[iro] == Empty) mrows_.emplace_back(iro, x);
            }
        }

        swap(mrows, mrows_);
        swap(mcols, mcols_);
    }

    int result{};
    for (const auto &row : rows) {
        result += accumulate(cbegin(row), cend(row), 0);
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int H, W;
    cin >> H >> W;

    vector<string> grid(H);
    for (auto &row : grid) {
        cin >> row;
        assert(sz(row) == W);
    }

    cout << cookies_num_remaining(grid) << '\n';
    return 0;
}
