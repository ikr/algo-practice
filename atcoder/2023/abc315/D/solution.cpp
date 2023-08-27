#include <bits/stdc++.h>
using namespace std;

using ValRep = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

vector<string> transpose(const vector<string> &m) {
    const auto H = ssize(m[0]);
    const auto W = ssize(m);

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
    return ssize(xs) == 1 && xs.front().second > 1;
}

vector<int> indices_to_mark(const vector<list<ValRep>> &xss) {
    vector<int> ans;
    for (int i = 0; i < ssize(xss); ++i) {
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
                     const int i) {}

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
        for (const auto i : mrows) {
        }

        for (const auto i : mcols) {
        }

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
        assert(ssize(row) == W);
    }

    cout << cookies_num_remaining(grid) << '\n';
    return 0;
}
