#include <bits/stdc++.h>
using namespace std;
using vc = vector<char>;

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

constexpr bool
is_possible(const unordered_set<pair<int, int>, PairHash<int, int>> &covered,
            const pair<int, int> coord) {
    return in_bounds(coord) && !covered.count(coord);
}

int matching_paths_count(const string &pattern) {
    unordered_set<pair<int, int>, PairHash<int, int>> covered{{0, 0}};
    int ans = 0;
    function<void(int, pair<int, int>)> recur;

    recur = [&recur, &pattern, &ans, &covered](const int i,
                                               const pair<int, int> coord) {
        if (coord == DEST_COORD) {
            if (i == DEST_I) ++ans;
            return;
        }

        for (const auto dir :
             pattern[i] == '?' ? vc{'U', 'D', 'L', 'R'} : vc{pattern[i]}) {
            const auto coord_prime = coord + delta(dir);

            if (!is_possible(covered, coord_prime)) continue;

            switch (dir) {
            case 'U':
                if (!is_possible(covered, coord_prime + delta('U')) &&
                    is_possible(covered, coord_prime + delta('L')) &&
                    is_possible(covered, coord_prime + delta('R')))
                    continue;
                break;

            case 'D':
                if (!is_possible(covered, coord_prime + delta('D')) &&
                    is_possible(covered, coord_prime + delta('L')) &&
                    is_possible(covered, coord_prime + delta('R')))
                    continue;
                break;

            case 'L':
                if (!is_possible(covered, coord_prime + delta('L')) &&
                    is_possible(covered, coord_prime + delta('U')) &&
                    is_possible(covered, coord_prime + delta('D')))
                    continue;
                break;

            case 'R':
                if (!is_possible(covered, coord_prime + delta('R')) &&
                    is_possible(covered, coord_prime + delta('U')) &&
                    is_possible(covered, coord_prime + delta('D')))
                    continue;
                break;
            }

            covered.insert(coord_prime);
            recur(i + 1, coord_prime);
            covered.erase(coord_prime);
        }
    };

    recur(0, {0, 0});

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string s;
    cin >> s;
    cout << matching_paths_count(s) << '\n';

    return 0;
}
