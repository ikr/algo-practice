#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int Size = 5;

constexpr bool in_tor(const int ro, const int co) {
    return 0 <= ro && ro < Size && 0 <= co && co < Size &&
           !(ro == 2 && co == 2);
}

int code_of(const vector<string> &grid) {
    int result{};
    for (int ro = 0; ro < Size; ++ro) {
        for (int co = 0; co < Size; ++co) {
            if (ro == 2 && co == 2) continue;
            if (grid[ro][co] == '#') result |= 1 << (ro * Size + co);
        }
    }
    return result;
}

int popcount_north(const int code) {
    int result{};
    const auto ro = 0;
    for (int co = 0; co < Size; ++co) {
        if (code & (ro * Size + co)) ++result;
    }
    return result;
}

int popcount_east(const int code) {
    int result{};
    const auto co = Size - 1;
    for (int ro = 0; ro < Size; ++ro) {
        if (code & (1 << (ro * Size + co))) ++result;
    }
    return result;
}

int popcount_south(const int code) {
    int result{};
    const auto ro = Size - 1;
    for (int co = 0; co < Size; ++co) {
        if (code & (ro * Size + co)) ++result;
    }
    return result;
}

int popcount_west(const int code) {
    int result{};
    const auto co = 0;
    for (int ro = 0; ro < Size; ++ro) {
        if (code & (1 << (ro * Size + co))) ++result;
    }
    return result;
}

using CodesByLevel = unordered_map<int, int>;
using Coord = pair<int, int>;

int same_level_neighs(const auto code, const Coord roco) {
    const auto [ro, co] = roco;
    int result{};
    for (const auto &[dro, dco] :
         vector<pair<int, int>>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {
        const auto ro_ = ro + dro;
        const auto co_ = co + dco;
        const auto x = ro_ * Size + co_;
        if (in_tor(ro_, co_) && (code & (1 << x))) ++result;
    }
    return result;
}

int neighs(const CodesByLevel &world, const int level, const Coord &roco) {
    const auto [ro, co] = roco;
    assert(!(ro == 2 && co == 2));
    auto result = same_level_neighs(world.at(level), roco);

    switch (auto x = ro * Size + co; x) {
    case 0:
        if (world.contains(level - 1)) {
            if (world.at(level - 1) & (1 << 7)) ++result;
            if (world.at(level - 1) & (1 << 11)) ++result;
        }
        break;

    case 1:
    case 2:
    case 3:
        if (world.contains(level - 1) && (world.at(level - 1) & (1 << 7))) {
            ++result;
        }
        break;

    case 4:
        if (world.contains(level - 1)) {
            if (world.at(level - 1) & (1 << 7)) ++result;
            if (world.at(level - 1) & (1 << 13)) ++result;
        }
        break;

    case 5:
    case 10:
    case 15:
        if (world.contains(level - 1) && (world.at(level - 1) & (1 << 11))) {
            ++result;
        }
        break;

    case 7:
        if (world.contains(level + 1)) {
            result += popcount_north(world.at(level + 1));
        }
        break;

    case 9:
    case 14:
    case 19:
        if (world.contains(level - 1) && (world.at(level - 1) & (1 << 13))) {
            ++result;
        }
        break;

    case 11:
        if (world.contains(level + 1)) {
            result += popcount_west(world.at(level + 1));
        }
        break;

    case 13:
        if (world.contains(level + 1)) {
            result += popcount_east(world.at(level + 1));
        }
        break;

    case 17:
        if (world.contains(level + 1)) {
            result += popcount_south(world.at(level + 1));
        }
        break;

    case 20:
        if (world.contains(level - 1)) {
            if (world.at(level - 1) & (1 << 11)) ++result;
            if (world.at(level - 1) & (1 << 17)) ++result;
        }
        break;

    case 21:
    case 22:
    case 23:
        if (world.contains(level - 1) && (world.at(level - 1) & (1 << 17))) {
            ++result;
        }
        break;

    case 24:
        if (world.contains(level - 1)) {
            if (world.at(level - 1) & (1 << 13)) ++result;
            if (world.at(level - 1) & (1 << 17)) ++result;
        }
        break;
    }

    return result;
}

int neighs(const vector<string> &grid, const int ro, const int co) {
    int result{};
    for (const auto &[dro, dco] :
         vector<pair<int, int>>{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}) {
        if (in_tor(ro + dro, co + dco) && grid[ro + dro][co + dco] == '#') {
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

int main() {
    vector<string> grid(Size);
    for (auto &row : grid) {
        cin >> row;
        assert(sz(row) == Size);
    }

    CodesByLevel world{{0, code_of(grid)}};
    return 0;
}
