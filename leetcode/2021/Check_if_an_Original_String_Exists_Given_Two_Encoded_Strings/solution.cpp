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

bool recur(map<pair<string, string>, bool> &memo, const string &a,
           const string &b) {
    const auto key = pair{a, b};
    const auto it = memo.find(key);
    if (it != cend(memo)) return it->second;

    const auto result = [&memo, &a, &b]() -> bool {
        if (a.empty() && b.empty()) return true;
        if (a.empty() != b.empty()) return false;

        if (!isdigit(a[0]) && !isdigit(b[0])) {
            if (a[0] != b[0]) return false;
            return recur(memo, a.substr(1), b.substr(1));
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
                        if (recur(memo, ra + a.substr(sz(na)),
                                  rb + b.substr(sz(nb)))) {
                            return true;
                        }
                    } else if (x < y) {
                        if (recur(memo, ra + a.substr(sz(na)),
                                  to_string(y - x) + rb + b.substr(sz(nb)))) {
                            return true;
                        }
                    } else {
                        assert(x > y);
                        if (recur(memo,
                                  to_string(x - y) + ra + a.substr(sz(na)),
                                  rb + b.substr(sz(nb)))) {
                            return true;
                        }
                    }
                }
            }

            return false;
        }

        if (!isdigit(b[0])) {
            const auto na = number_prefix(a);
            for (int i = 1; i <= sz(na); ++i) {
                const int x = stoi(na.substr(0, i));
                const auto ra = na.substr(i);

                if (x == 0) {
                    if (recur(memo, ra + a.substr(sz(na)), b)) {
                        return true;
                    }
                } else if (x == 1) {
                    if (recur(memo, ra + a.substr(sz(na)), b.substr(1))) {
                        return true;
                    }
                } else {
                    assert(x > 1);
                    if (recur(memo, to_string(x - 1) + ra + a.substr(sz(na)),
                              b.substr(1))) {
                        return true;
                    }
                }
            }

            return false;
        }

        assert(!isdigit(a[0]));
        assert(isdigit(b[0]));

        const auto nb = number_prefix(b);
        for (int j = 1; j <= sz(nb); ++j) {
            const int y = stoi(nb.substr(0, j));
            const auto rb = nb.substr(j);

            if (y == 0) {
                if (recur(memo, a, rb + b.substr(sz(nb)))) {
                    return true;
                }
            } else if (y == 1) {
                if (recur(memo, a.substr(1), rb + b.substr(sz(nb)))) {
                    return true;
                }
            } else {
                assert(y > 1);
                if (recur(memo, a.substr(1),
                          to_string(y - 1) + rb + b.substr(sz(nb)))) {
                    return true;
                }
            }
        }

        return false;
    }();

    memo[key] = result;
    return result;
}

struct Solution final {
    bool possiblyEquals(const string &a, const string &b) const {
        map<pair<string, string>, bool> memo;
        return recur(memo, a, b);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example A") {
        const auto actual = Solution{}.possiblyEquals(
            "2ternationali32ninternationa21ation", "i18ni18n");
        const auto expected = true;
        EXPECT(actual == expected);
    },
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
    CASE("Test case 101") {
        const auto actual = Solution{}.possiblyEquals(
            "8q42g7q1g27g735g929g2q62g235q7", "9g6g8g128g46q1q74g419q419q9q11");
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("Test case 102") {
        const auto actual = Solution{}.possiblyEquals(
            "g71g15q581g59g67g3q599q56g87g", "44q4g31g7q636g699g383g44q453g");
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("Test case 103") {
        const auto actual = Solution{}.possiblyEquals(
            "1q955g8g8q18q7g1g63q73q6g7g1g73", "43q968g34q731q98g778q2q6g48g78g");
        const auto expected = false;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
