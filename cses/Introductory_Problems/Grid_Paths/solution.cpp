#include <bits/stdc++.h>
using namespace std;

static constexpr int RO_MAX = 6;
static constexpr int CO_MAX = 6;
static constexpr int DEST_I = (RO_MAX + 1) * (CO_MAX + 1) - 1;
static constexpr pair<int, int> DEST_COORD{6, 0};

template <typename T>
constexpr pair<T, T> operator+(const pair<T, T> &lhs, const pair<T, T> &rhs) {
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

template <typename T1, typename T2> struct PairHash final {
    size_t operator()(const pair<T1, T2> &p) const {
        return 31 * hash<T1>{}(p.first) + hash<T2>{}(p.second);
    }
};

constexpr pair<int, int> delta(const char dir) {
    switch (dir) {
    case 'U':
        return {-1, 0};
    case 'D':
        return {1, 0};
    case 'L':
        return {0, -1};
    case 'R':
        return {0, 1};
    default:
        assert(false && "Invalid direction char");
        return {0, 0};
    }
}

constexpr bool in_bounds(const pair<int, int> coord) {
    const auto [ro, co] = coord;
    return ro >= 0 && ro <= RO_MAX && co >= 0 && co <= CO_MAX;
}

int matching_paths_count(const string &pattern) {
    unordered_set<pair<int, int>, PairHash<int, int>> covered;
    int ans = 0;
    function<void(int, pair<int, int>)> recur;

    recur = [&pattern, &ans, &covered](const int i,
                                       const pair<int, int> coord) {
        if (coord == DEST_COORD && i != DEST_I) return;
    };

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;

    return 0;
}
