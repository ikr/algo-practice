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

struct LightbulbRow final {
    string solve(const string &xs, const int i0, const int g) const {
        const int curr = inof(count(cbegin(xs), cend(xs), 'O'));

        string ans(i0, '<');

        for (int i = 0, to_turn_on = g - curr;
             (i < sz(xs)) && (to_turn_on != 0); ++i) {
            if (to_turn_on > 0) {
                if (xs[i] == 'X') {
                    ans += 'S';
                    --to_turn_on;
                }
            } else {
                assert(to_turn_on < 0);

                if (xs[i] == 'O') {
                    ans += 'S';
                    ++to_turn_on;
                }
            }

            if (i + 1 < sz(xs)) {
                ans += '>';
            } else {
                assert(to_turn_on == 0);
            }
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = LightbulbRow{}.solve("XXXXXXXXXX", 4, 3);
        const auto expected = string{"<<<<S>S>S>"};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = LightbulbRow{}.solve("XXXXOOOXXX", 0, 3);
        const auto expected = string{""};
        EXPECT(actual == expected);
    },
    CASE("A") {
        const auto actual = LightbulbRow{}.solve("X", 0, 1);
        const auto expected = string{"S"};
        EXPECT(actual == expected);
    },
    CASE("B") {
        const auto actual = LightbulbRow{}.solve("O", 0, 0);
        const auto expected = string{"S"};
        EXPECT(actual == expected);
    },
    CASE("shift left and switch all on") {
        const auto actual = LightbulbRow{}.solve("XXX", 2, 3);
        const auto expected = string{"<<S>S>S"};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
