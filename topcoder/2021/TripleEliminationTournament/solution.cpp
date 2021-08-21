#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T>
constexpr typename vector<T>::const_iterator cbegin(const vector<T> &xs) {
    return xs.cbegin();
}

template <typename T>
constexpr typename vector<T>::const_iterator cend(const vector<T> &xs) {
    return xs.cend();
}

string::const_iterator cbegin(const string &xs) { return xs.cbegin(); }
string::const_iterator cend(const string &xs) { return xs.cend(); }

using Groups = array<int, 4>;

Groups::const_iterator cbegin(const Groups &xs) { return xs.cbegin(); }
Groups::const_iterator cend(const Groups &xs) { return xs.cend(); }

bool is_over(const Groups &xs) {
    const auto it = find(cbegin(xs), cend(xs), 1);
    if (it == cend(xs)) return false;
    const auto i0 = inof(distance(cbegin(xs), it));
    if (i0 == 3) return false;

    for (int i = i0 + 1; i <= 2; ++i) {
        if (xs[i]) return false;
    }

    return true;
}

pair<Groups, int> next_gen_with_games_num(Groups g, const int winner_group) {
    g[3] = 0;

    Groups g_{};
    int num = 0;

    for (int i = 0; i < 3; ++i) {
        int x = g[i];
        if (!x) continue;

        if (x / 2) {
            num += x / 2;
            g_[i] += x / 2;
            g_[i + 1] += x / 2;
        }

        if (x % 2) {
            const int j = [&]() -> int {
                if (g[i + 1]) return i + 1;
                if (i + 2 < 3 && g[i + 2]) return i + 2;
                return -1;
            }();

            if (j >= 0) {
                ++num;
                if (winner_group == i) {
                    ++g_[i];
                    ++g_[j + 1];
                } else {
                    ++g_[i + 1];
                    ++g_[j];
                }
            } else { // No one to play with
                ++g_[i];
            }
        }
    }

    return {g_, num};
}

ostream &operator<<(ostream &os, const Groups &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

struct TripleEliminationTournament final {
    int countGames(const int n, const int winner_group) const {
        Groups g{n, 0, 0, 0};
        int ans = 0;

        while (!is_over(g)) {
            cerr << g << endl;

            const auto p = next_gen_with_games_num(g, winner_group);
            const auto g_ = p.first;
            const auto num = p.second;

            ans += num;
            g = g_;
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = TripleEliminationTournament{}.countGames(2, 0);
        const auto expected = 3;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = TripleEliminationTournament{}.countGames(3, 1);
        const auto expected = 7;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = TripleEliminationTournament{}.countGames(8, 0);
        const auto expected = 21;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = TripleEliminationTournament{}.countGames(436475, 2);
        const auto expected = 1309424;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
