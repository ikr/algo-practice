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

pair<array<int, 3>, optional<int>>
freqs_and_an_index_of_dot(const string &seq) {
    array<int, 3> fs{};
    optional<int> index_of_dot;

    for (int i = 0; i < sz(seq); ++i) {
        switch (seq[i]) {
        case '.':
            ++fs[0];
            index_of_dot = i;
            break;

        case 'X':
            ++fs[1];
            break;

        case 'O':
            ++fs[2];
            break;

        default:
            assert(false && "Unexpected char");
            break;
        }
    }

    assert(fs[1] != sz(seq));
    assert(fs[2] != sz(seq));
    assert(fs[0] + fs[1] + fs[2] == sz(seq));
    return {fs, index_of_dot};
}

constexpr optional<int> xs_to_win(const array<int, 3> &fs) {
    if (fs[2] > 0) return nullopt;
    return fs[0];
}

optional<pii> min_xs(const vector<string> &grid) {
    map<int, int> alts_by_xs;
    set<pii> singles;

    for (int i = 0; i < sz(grid); ++i) {
        for (const auto &[seq, is_row] :
             {pair{grid[i], true}, pair{column(grid, i), false}}) {
            const auto [fs, dot] = freqs_and_an_index_of_dot(seq);
            if (xs_to_win(fs)) {
                const int k = *xs_to_win(fs);
                ++alts_by_xs[k];

                if (k == 1) {
                    assert(dot);

                    if (is_row) {
                        singles.emplace(i, *dot);
                    } else {
                        singles.emplace(*dot, i);
                    }
                }
            }
        }
    }

    if (alts_by_xs.empty()) return nullopt;
    const auto [a, b] = *cbegin(alts_by_xs);

    return a == 1 ? pair{1, sz(singles)} : pair{a, b};
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
