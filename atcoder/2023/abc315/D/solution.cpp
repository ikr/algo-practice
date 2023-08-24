#include <bits/stdc++.h>
using namespace std;

using ValRep = pair<int, int>;

static constexpr int Az = 26;

vector<ValRep> run_length_encoding(const string &xs) {
    assert(!empty(xs));
    vector<ValRep> result{{xs[0], 1}};
    for (const auto x : xs | views::drop(1)) {
        if (result.back().first == x) {
            ++(result.back().second);
        } else {
            result.emplace_back(x, 1);
        }
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

    return 0;
}
