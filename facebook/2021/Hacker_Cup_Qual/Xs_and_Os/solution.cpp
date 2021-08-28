#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string column(const vector<string> &grid, const int i) {
    string ans(sz(grid), ' ');
    for (int j = 0; j < sz(grid); ++j) {
        ans[j] = grid[j][i];
    }
    return ans;
}

array<int, 3> freqs(const string &seq) {
    array<int, 3> ans{};

    for (const auto a : seq) {
        switch (a) {
        case '.':
            ++ans[0];
            break;

        case 'X':
            ++ans[1];
            break;

        case 'O':
            ++ans[2];
            break;

        default:
            assert(false && "Unexpected char");
            break;
        }
    }

    assert(ans[1] != sz(seq));
    assert(ans[2] != sz(seq));
    assert(ans[0] + ans[1] + ans[2] == sz(seq));
    return ans;
}

optional<int> xs_to_win(const string &seq) {
    const auto fs = freqs(seq);
    if (fs[2] > 0) return nullopt;
    return fs[0];
}

optional<pii> min_xs(const vector<string> &grid) {
    map<int, int> alts_by_xs;

    for (int i = 0; i < sz(grid); ++i) {
        for (const auto &seq : {grid[i], column(grid, i)}) {
            const auto candidate = xs_to_win(seq);

            if (candidate) {
                ++alts_by_xs[*candidate];
            }
        }
    }

    if (alts_by_xs.empty()) return nullopt;
    return *cbegin(alts_by_xs);
}

string represent(const optional<pii> &ab) {
    if (!ab) return "Impossible";

    const auto [a, b] = *ab;
    stringstream ss;
    ss << a << ' ' << b;

    return ss.str();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n;
        cin >> n;

        vector<string> grid(n);
        for (auto &row : grid) cin >> row;

        cout << "Case #" << i << ": " << represent(min_xs(grid)) << '\n';
    }

    return 0;
}
