#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string number_prefix(const string &xs) {
    string result;

    for (auto it = cbegin(xs); it != cend(xs) && isdigit(*it); ++it) {
        result += *it;
    }

    assert(!result.empty());
    assert(sz(result) <= 3);
    return result;
}

bool recur(const string &a, const string &b) {
    if (a.empty() && b.empty()) return true;
    if (a.empty() != b.empty()) return false;

    if (!isdigit(a[0]) && !isdigit(b[0])) {
        if (a[0] != b[0]) return false;
        return recur(a.substr(1), b.substr(1));
    }

    if (isdigit(a[0]) && isdigit(b[0])) {
        const auto na = number_prefix(a);
        const auto nb = number_prefix(b);

        for (int i = 1; i <= sz(na); ++i) {
            for (int j = 1; j <= sz(nb); ++j) {
                const int x = stoi(na.substr(0, i));
                const int y = stoi(nb.substr(0, j));

                const auto ra = na.substr(i);
                const auto rb = nb.substr(j);

                if (x == y) {
                    if (recur(ra + a.substr(sz(na)), rb + b.substr(sz(nb)))) {
                        return true;
                    }
                } else if (x < y) {
                    if (recur(ra + a.substr(sz(na)),
                              to_string(y - x) + rb + b.substr(sz(nb)))) {
                        return true;
                    }
                } else {
                    assert(x > y);
                    if (recur(to_string(x - y) + ra + a.substr(sz(na)),
                              rb + b.substr(sz(nb)))) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    if (!isdigit(b[0])) return recur(b, a);
    assert(!isdigit(a[0]));
    assert(isdigit(b[0]));

    const auto nb = number_prefix(b);
    for (int j = 1; j <= sz(nb); ++j) {
        const int y = stoi(nb.substr(0, j));
        const auto rb = nb.substr(j);

        if (y == 0) {
            if (recur(a, rb + b.substr(sz(nb)))) {
                return true;
            }
        } else if (y == 1) {
            if (recur(a.substr(1), rb + b.substr(sz(nb)))) {
                return true;
            }
        } else {
            assert(y > 1);
            if (recur(a.substr(1), to_string(y - 1) + rb + b.substr(sz(nb)))) {
                return true;
            }
        }
    }

    return false;
}

struct Solution final {
    bool possiblyEquals(const string &a, const string &b) const {
        return recur(a, b);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 1") {
        const auto actual = Solution{}.possiblyEquals("internationalization", "i18n");
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = Solution{}.possiblyEquals("l123e", "44");
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = Solution{}.possiblyEquals("a5b", "c5b");
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = Solution{}.possiblyEquals("112s", "g841");
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("Example 5") {
        const auto actual = Solution{}.possiblyEquals("ab", "a2");
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("111 and 84") {
        const auto actual = Solution{}.possiblyEquals("111", "84");
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("6aa and 23aa") {
        const auto actual = Solution{}.possiblyEquals("6aa", "23aa");
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("Test case 28") {
        const auto actual = Solution{}.possiblyEquals("4p6p9p87q11", "p857q3q27");
        const auto expected = false;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
