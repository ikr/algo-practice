#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int Size = 5;

constexpr bool in_bounds(const int ro, const int co) {
    return 0 <= ro && ro < Size && 0 <= co && co < Size;
}

int neighs(const vector<string> &grid, const int ro, const int co) {
    int result{};
    for (const auto &[dro, dco] :
         vector<pair<int, int>>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {
        if (in_bounds(ro + dro, co + dco) && grid[ro + dro][co + dco] == '#') {
            ++result;
        }
    }
    return result;
}

vector<string> new_gen(const vector<string> &grid) {
    vector<string> result(grid);

    for (int ro = 0; ro < Size; ++ro) {
        for (int co = 0; co < Size; ++co) {
            const auto n = neighs(grid, ro, co);

            if (grid[ro][co] == '#' && n != 1) {
                result[ro][co] = '.';
            } else if (grid[ro][co] == '.' && (n == 1 || n == 2)) {
                result[ro][co] = '#';
            }
        }
    }

    return result;
}

int code(const vector<string> &grid) {
    int result{};

    for (int ro = 0; ro < Size; ++ro) {
        for (int co = 0; co < Size; ++co) {
            if (grid[ro][co] == '#') {
                result += 1 << (ro * Size + co);
            }
        }
    }

    return result;
}

int main() {
    vector<string> grid(Size);
    for (auto &row : grid) {
        cin >> row;
        assert(sz(row) == Size);
    }

    unordered_set<int> codes{code(grid)};

    for (;;) {
        auto grid_ = new_gen(grid);
        const auto c = code(grid_);
        if (codes.contains(c)) {
            cout << c << '\n';
            break;
        }

        codes.insert(c);
        swap(grid, grid_);
    }
    return 0;
}
