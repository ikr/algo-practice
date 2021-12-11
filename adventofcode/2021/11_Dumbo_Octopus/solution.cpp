#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int count_zeros(const vvi &grid) {
    return transform_reduce(
        cbegin(grid), cend(grid), 0, plus<int>{},
        [](const vi &row) { return count(cbegin(row), cend(row), 0); });
}

void evolve(vvi &grid, const int ro, const int co) {
    ++grid[ro][co];
    grid[ro][co] %= 10;
}

constexpr bool in_bounds(const pii dim, const pii roco) {
    const auto [H, W] = dim;
    const auto [ro, co] = roco;
    return 0 <= ro && ro < H && 0 <= co && co < W;
}

void flash_and_enqueue_chained(vvi &grid, queue<pii> chained, const int ro,
                               const int co) {
    assert(grid[ro][co] == 0);
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    for (int dro = -1; dro <= 1; ++dro) {
        for (int dco = -1; dco <= 1; ++dco) {
            if (!dro && !dco) continue;
            const auto ro_ = ro + dro;
            const auto co_ = co + dco;
            if (!in_bounds({H, W}, {ro_, co_})) continue;

            if (grid[ro_][co_] == 0) continue;
            evolve(grid, ro_, co_);
            if (grid[ro_][co_] == 0) chained.emplace(ro_, co_);
        }
    }
}

vvi evolve(vvi grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    queue<pii> chained;
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            evolve(grid, ro, co);
            if (grid[ro][co] == 0) chained.emplace(ro, co);
        }
    }

    while (!chained.empty()) {
        const auto [ro, co] = chained.front();
        chained.pop();
        flash_and_enqueue_chained(grid, chained, ro, co);
    }

    return grid;
}

int count_total_flashes(vvi grid, const int steps) {
    for (int i = 0; i < steps; ++i) grid = evolve(grid);
    return count_zeros(grid);
}

int main() {
    vvi grid;

    for (string line; getline(cin, line);) {
        vi xs(sz(line));
        transform(cbegin(line), cend(line), begin(xs),
                  [](const char d) { return inof(d) - inof('0'); });
        grid.push_back(xs);
    }

    cout << count_total_flashes(grid, 1) << '\n';
    return 0;
}
