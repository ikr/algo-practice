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

template <typename T>
optional<T> first_outside_intersection(const set<T> &a, const set<T> &b) {
    set<T> x;
    set_intersection(cbegin(a), cend(a), cbegin(b), cend(b),
                     inserter(x, cbegin(x)));

    for (const auto i : a) {
        if (!x.count(i)) return i;
    }

    for (const auto i : b) {
        if (!x.count(i)) return i;
    }

    return nullopt;
}

void flash(vvi &grid, set<pii> &flashing, const int ro, const int co) {
    assert(grid[ro][co] == 0);
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    for (int dro = -1; dro <= 1; ++dro) {
        for (int dco = -1; dco <= 1; ++dco) {
            if (!dro && !dco) continue;
            const auto ro_ = ro + dro;
            const auto co_ = co + dco;
            if (!in_bounds({H, W}, {ro_, co_})) continue;

            if (flashing.count(pii{ro_, co_})) continue;
            evolve(grid, ro_, co_);
            if (grid[ro_][co_] == 0) flashing.emplace(ro_, co_);
        }
    }
}

vvi evolve(vvi grid) {
    const auto H = sz(grid);
    const auto W = sz(grid[0]);

    set<pii> flashing;
    for (int ro = 0; ro < H; ++ro) {
        for (int co = 0; co < W; ++co) {
            evolve(grid, ro, co);
            if (grid[ro][co] == 0) flashing.emplace(ro, co);
        }
    }

    set<pii> flashed;
    for (;;) {
        const auto roco = first_outside_intersection(flashing, flashed);
        if (!roco) break;

        const auto [ro, co] = *roco;
        flash(grid, flashing, ro, co);
        flashed.emplace(ro, co);
    }

    return grid;
}

int count_total_flashes(vvi grid, const int steps) {
    int ans{};
    for (int i = 0; i < steps; ++i) {
        grid = evolve(grid);
        ans += count_zeros(grid);
    }
    return ans;
}

int main() {
    vvi grid;

    for (string line; getline(cin, line);) {
        vi xs(sz(line));
        transform(cbegin(line), cend(line), begin(xs),
                  [](const char d) { return inof(d) - inof('0'); });
        grid.push_back(xs);
    }

    cout << count_total_flashes(grid, 100) << '\n';
    return 0;
}
