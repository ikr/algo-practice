#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

struct IHWCPenalty final {
    string resolve(const string &xs) const {
        int lo{};
        int up{};

        string ans;
        for (const auto x : xs) {
            switch (x) {
            case 'p':
                --lo;
                break;
            case 's':
                ++lo;
                break;
            case 'g':
                if (lo == up) {
                    ans += '=';
                } else if (lo > up) {
                    ans += 'P';
                    ++up;
                } else {
                    ans += 'S';
                }
                break;

            case 'P':
                --up;
                break;
            case 'S':
                ++up;
                break;
            case 'G':
                if (lo == up) {
                    ans += '=';
                } else if (up > lo) {
                    ans += 'P';
                    ++lo;
                } else {
                    ans += 'S';
                }
                break;

            default:
                assert(false && "/o\\");
            }
        }
        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = IHWCPenalty{}.resolve("gggGgGg");
        const auto expected = string{"======="};
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = IHWCPenalty{}.resolve("PPggg");
        const auto expected = string{"PP="};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
