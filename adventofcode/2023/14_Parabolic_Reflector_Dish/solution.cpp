#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static constexpr ll Cycles = 1000000000LL;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> transpose(const vector<string> &m) {
    const auto H = sz(m[0]);
    const auto W = sz(m);

    vector<string> ans(H, string(W, ' '));
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            ans[ro][co] = m[co][ro];
        }
    }
    return ans;
}

void roll_west(string &xs) {
    const auto slide_left = [&](int i) {
        assert(xs[i] == 'O');
        for (;;) {
            if (i == 0 || xs[i - 1] != '.') return;
            swap(xs[i], xs[i - 1]);
            --i;
        }
    };

    int i = 0;
    for (;;) {
        const auto is = xs.find('O', i);
        if (is == string::npos) return;
        slide_left(inof(is));
        ++i;
    }
}

void roll_east(string &xs) {
    ranges::reverse(xs);
    roll_west(xs);
    ranges::reverse(xs);
}

void roll_all_west(vector<string> &grid) {
    for (auto &row : grid) roll_west(row);
}

void roll_all_east(vector<string> &grid) {
    for (auto &row : grid) roll_east(row);
}

void roll_all_north(vector<string> &grid) {
    grid = transpose(grid);
    roll_all_west(grid);
    grid = transpose(grid);
}

void roll_all_south(vector<string> &grid) {
    grid = transpose(grid);
    roll_all_east(grid);
    grid = transpose(grid);
}

int total_load_west(const vector<string> &grid) {
    const auto W = sz(grid[0]);
    int result{};
    for (auto &row : grid) {
        for (int co = 0; co < W; ++co) {
            if (row[co] == 'O') {
                result += W - co;
            }
        }
    }
    return result;
}

int total_load_north(vector<string> grid) {
    grid = transpose(grid);
    return total_load_west(grid);
}

template <typename T>
bool is_at(const vector<T> &haystack, const vector<T> &needle, const int i) {
    for (int j = 0; j < sz(needle); ++j) {
        if (haystack[i + j] != needle[j]) return false;
    }

    return true;
}

template <typename T> int tail_period(const vector<T> &xs) {
    const auto marker_size = 32;
    const vector marker(cend(xs) - marker_size, cend(xs));
    assert(is_at(xs, marker, sz(xs) - marker_size));

    for (int i = sz(xs) - marker_size - 1; i >= 0; --i) {
        if (is_at(xs, marker, i)) {
            return sz(xs) - marker_size - i;
        }
    }

    return -1;
}

int main() {
    vector<string> grid;
    for (string line; getline(cin, line);) grid.push_back(line);

    vector<int> xs;
    for (int i = 1; i <= 1000; ++i) {
        roll_all_north(grid);
        roll_all_west(grid);
        roll_all_south(grid);
        roll_all_east(grid);
        xs.push_back(total_load_north(grid));
    }

    const ll P = tail_period(xs);
    vector<int> cycle(P);
    for (int i = 0; i < P; ++i) cycle[P - 1 - i] = xs[sz(xs) - 1 - i];
    const auto last_cycle_begin_index = sz(xs) - P;
    cout << cycle[(Cycles - 1 - last_cycle_begin_index) % P] << '\n';
    return 0;
}
