#include <bits/stdc++.h>
using namespace std;

using ValRep = pair<int, int>;

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

int cookies_num_remaining(const vector<string> &grid) {
    vector<list<ValRep>> rows(size(grid));
    ranges::transform(grid, begin(rows), run_length_encoding);

    assert(!empty(grid));
    vector<list<ValRep>> cols(size(grid[0]));
    ranges::transform(transpose(grid), begin(cols), run_length_encoding);

    return -1;
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
