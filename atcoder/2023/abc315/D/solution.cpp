#include <bits/stdc++.h>
using namespace std;

using ValRep = pair<int, int>;

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

list<ValRep> run_length_encoding(const string &xs) {
    assert(!empty(xs));
    list<ValRep> result{{xs[0], 1}};
    for (const auto x : xs | views::drop(1)) {
        if (result.back().first == x) {
            ++result.back().second;
        } else {
            result.emplace_back(x - 'a', 1);
        }
    }
    return result;
}

constexpr bool should_be_marked(const list<ValRep> &xs) {
    return sz(xs) == 1 && xs.front().second > 1;
}

vector<int> indices_to_mark(const vector<list<ValRep>> &xss) {
    vector<int> ans;
    for (auto i = sz(xss) - 1; i >= 0; --i) {
        if (should_be_marked(xss[i])) ans.push_back(i);
    }
    return ans;
}

int number_of_dominated(const vector<int> &xs, const int hi) {
    return inof(lower_bound(cbegin(xs), cend(xs), hi) - cbegin(xs));
}

list<ValRep>::iterator skip_k(list<ValRep> &xs, const int k) {
    int skipped{};
    for (auto it = begin(xs); it != end(xs); ++it) {
        skipped += it->second;
        if (skipped > k) return it;
    }
    return end(xs);
}

void remove_at_index(const vector<int> hole_indices, list<ValRep> &xs,
                     const int i) {
    const auto it = skip_k(xs, i - number_of_dominated(hole_indices, i));
    assert(it != end(xs));
    if (it->second == 1) {
        const auto lit = it == begin(xs) ? end(xs) : prev(it);
        const auto rit = xs.erase(it);

        if (lit != cend(xs) && rit != cend(xs) && lit->first == rit->first) {
            lit->second += rit->second;
            xs.erase(rit);
        }
    } else {
        --it->second;
    }
}

int cookies_num_remaining(const vector<string> &grid) {
    vector<list<ValRep>> rows(size(grid));
    ranges::transform(grid, begin(rows), run_length_encoding);

    assert(!empty(grid));
    vector<list<ValRep>> cols(size(grid[0]));
    ranges::transform(transpose(grid), begin(cols), run_length_encoding);

    auto mrows = indices_to_mark(rows);
    auto mcols = indices_to_mark(cols);

    vector<int> mrows_;
    vector<int> mcols_;

    vector<int> xrows;
    vector<int> xcols;

    while (!mrows.empty() || !mcols.empty()) {
        for (const auto iro : mrows) {
            cerr << "Deleting row " << iro << endl;

            for (auto ico = sz(cols) - 1; ico >= 0; --ico) {
                if (empty(cols[ico])) continue;

                remove_at_index(xrows, cols[ico], iro);
                if (sz(cols[ico]) == 1 && cols[ico].front().second > 1) {
                    mcols_.push_back(ico);
                }
            }
        }

        for (const auto ico : mcols) {
            cerr << "Deleting col " << ico << endl;

            for (auto iro = sz(rows) - 1; iro >= 0; --iro) {
                if (empty(rows[iro])) continue;

                remove_at_index(xcols, rows[iro], ico);
                if (sz(rows[iro]) == 1 && rows[iro].front().second > 1) {
                    mrows_.push_back(iro);
                }
            }
        }

        xrows.insert(end(xrows), cbegin(mrows), cend(mrows));
        xcols.insert(end(xcols), cbegin(mcols), cend(mcols));
        ranges::sort(xrows);
        ranges::sort(xcols);

        swap(mrows, mrows_);
        swap(mcols, mcols_);
    }

    int result{};
    for (const auto &row : rows) {
        for (const auto &[_, k] : row) result += k;
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
