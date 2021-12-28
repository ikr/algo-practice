#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

void skip_cin_line() {
    string s;
    getline(cin, s);
}

vector<string> enlarge_canvas(const int d, const vector<string> &src) {
    const int H = sz(src) + 2 * d;
    const int W = sz(src[0]) + 2 * d;
    vector<string> result(H, string(W, '.'));

    for (int ro = 0; ro < sz(src); ++ro) {
        for (int co = 0; co < sz(src[0]); ++co) {
            result[ro + d][co + d] = src[ro][co];
        }
    }

    return result;
}

vector<string> evolve(const string &pad, const vector<string> &grid,
                      const char infval) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    const auto in_bounds = [&](const pii roco) -> bool {
        const auto [ro, co] = roco;
        return 0 <= ro && ro < H && 0 <= co && co < W;
    };

    const auto safe_get = [&](const pii roco) -> char {
        const auto [ro, co] = roco;
        return in_bounds(roco) ? grid[ro][co] : infval;
    };

    const auto locality_bits = [&](const pii roco) -> int {
        const auto [ro, co] = roco;
        string x;

        for (int dro = -1, i = 0; dro <= 1; ++dro) {
            for (int dco = -1; dco <= 1; ++dco, ++i) {
                x += safe_get({ro + dro, co + dco});
            }
        }

        bitset<9> bits(x, 0, 9, '.', '#');
        return inof(bits.to_ulong());
    };

    vector<string> result = grid;

    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            result[ro][co] = pad[locality_bits({ro, co})];
        }
    }

    return result;
}

void print_grid(const vector<string> &grid) {
    for (const auto &row : grid) {
        cerr << row << endl;
    }
    cerr << endl;
}

int main() {
    string pad;
    cin >> pad;
    skip_cin_line();
    skip_cin_line();

    vector<string> src;
    for (string row; getline(cin, row);) src.push_back(row);

    src = enlarge_canvas(150, src);
    print_grid(src);

    for (int step = 0; step < 50; ++step) {
        src = evolve(pad, src, step % 2 ? '#' : '.');
        print_grid(src);
    }

    int ans{};
    for (const auto &row : src) {
        ans += inof(count(cbegin(row), cend(row), '#'));
    }
    cout << ans << '\n';
    return 0;
}
