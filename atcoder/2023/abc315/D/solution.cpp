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

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T, size_t N>
ostream &operator<<(ostream &os, const vector<array<T, N>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

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
    for (int i = 0; i < sz(xss); ++i) {
        const auto mbx = markable_value(xss[i]);
        if (mbx) result.emplace_back(i, *mbx);
    }
    return result;
}

constexpr bool contains_index(const vector<pii> &ixs, const int i) {
    return ranges::any_of(ixs, [i](const auto &ix) { return ix.first == i; });
}

int cookies_num_remaining(const vector<string> &grid) {
    vector<Freq> rows(size(grid));
    ranges::transform(grid, begin(rows), frequences);

    assert(!empty(grid));
    vector<Freq> cols(size(grid[0]));
    ranges::transform(transpose(grid), begin(cols), frequences);

    auto mrows = indices_to_mark(rows);
    auto mcols = indices_to_mark(cols);

    // cerr << "mrows: " << mrows << endl;
    // cerr << "mcols: " << mcols << endl;

    while (!mrows.empty() || !mcols.empty()) {
        vector<pii> mrows_;
        vector<pii> mcols_;

        for (const auto &[iro, x] : mrows) {
            for (int ico = 0; ico < sz(cols); ++ico) {
                if (cols[ico] == Empty || contains_index(mcols, ico)) continue;
                if (cols[ico][x]) --cols[ico][x];

                const auto mbx = markable_value(cols[ico]);
                if (mbx && !contains_index(mcols_, ico)) {
                    mcols_.emplace_back(ico, *mbx);
                }
            }
            rows[iro].fill(0);
        }

        for (const auto &[ico, x] : mcols) {
            for (int iro = 0; iro < sz(rows); ++iro) {
                if (rows[iro] == Empty) continue;
                if (rows[iro][x]) --rows[iro][x];

                if (rows[iro] == Empty) mrows_.emplace_back(iro, x);
                const auto mbx = markable_value(rows[iro]);
                if (mbx && !contains_index(mrows_, iro)) {
                    mrows_.emplace_back(iro, *mbx);
                }
            }
            cols[ico].fill(0);
        }

        swap(mrows, mrows_);
        swap(mcols, mcols_);
        // cerr << "mrows: " << mrows << endl;
        // cerr << "mcols: " << mcols << endl;
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
