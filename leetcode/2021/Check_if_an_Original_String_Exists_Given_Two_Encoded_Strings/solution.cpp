#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vi distinct(vi xs) {
    sort(begin(xs), end(xs));
    xs.erase(unique(begin(xs), end(xs)), end(xs));
    return xs;
}

vi numeral_alternatives(const string &xs) {
    assert(
        all_of(cbegin(xs), cend(xs), [](const auto x) { return isdigit(x); }));
    if (sz(xs) == 1) return {stoi(xs)};
    if (sz(xs) == 2) {
        return {stoi(xs.substr(0, 1)) + stoi(xs.substr(1)), stoi(xs)};
    }

    assert(sz(xs) == 3);
    return distinct(
        {stoi(xs),
         stoi(xs.substr(0, 1)) + stoi(xs.substr(1, 1)) + stoi(xs.substr(2)),
         stoi(xs.substr(0, 2)) + stoi(xs.substr(2)),
         stoi(xs.substr(0, 1)) + stoi(xs.substr(1))});
}

vector<string> split_into_parts(const string &xs) {
    assert(!xs.empty());
    vector<string> result;
    string curr{xs[0]};

    for (int i = 1; i < sz(xs); ++i) {
        if (isdigit(curr.back()) == isdigit(xs[i])) {
            curr += xs[i];
            continue;
        }

        result.push_back(curr);
        curr = string{xs[i]};
    }

    if (!curr.empty()) result.push_back(curr);
    return result;
}

vvi part_selector(const string &part) {
    assert(!part.empty());

    if (isdigit(part[0])) {
        return {numeral_alternatives(part)};
    }

    assert(all_of(cbegin(part), cend(part),
                  [](const auto x) { return !isdigit(x); }));

    vvi result(sz(part));
    transform(cbegin(part), cend(part), begin(result),
              [](const char x) { return vi{-inof(x)}; });
    return result;
}

vvi full_selector(const string &xs) {
    const auto parts = split_into_parts(xs);
    vvi result;

    for (const auto &p : parts) {
        const auto s = part_selector(p);
        result.insert(cend(result), cbegin(s), cend(s));
    }

    return result;
}

int match_length(const vi &instance) {
    return transform_reduce(cbegin(instance), cend(instance), 0, plus<int>{},
                            [](const int x) {
                                assert(x != 0);
                                return x < 0 ? 1 : x;
                            });
}

bool confirm_match(vi instance_a, vi instance_b) {
    auto it = begin(instance_a);
    auto jt = begin(instance_b);

    while (it != end(instance_a) && jt != end(instance_b)) {
        assert(*it != 0 && *jt != 0);

        if (*it < 0 && *jt < 0) {
            if (*it != *jt) return false;
            ++it;
            ++jt;
            continue;
        }

        if (*it > 0 && *jt > 0) {
            if (*it == *jt) {
                ++it;
                ++jt;
                continue;
            }

            const auto d = min(*it, *jt);
            *it -= d;
            *jt -= d;
            if (*it == 0) ++it;
            if (*jt == 0) ++jt;
            continue;
        }

        if (*it < 0) {
            assert(*jt > 0);
            ++it;
            --(*jt);
            if (*jt == 0) ++jt;
            continue;
        }

        assert(*it > 0);
        assert(*jt < 0);
        --(*it);
        if (*it == 0) ++jt;
        ++jt;
    }

    return it == end(instance_a) && jt == end(instance_b);
}

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
    CASE("numeral_alternatives(7)") {
        const auto actual = numeral_alternatives("7");
        const auto expected = vi{7};
        EXPECT(actual == expected);
    },
    CASE("numeral_alternatives(23)") {
        const auto actual = numeral_alternatives("23");
        const auto expected = vi{5, 23};
        EXPECT(actual == expected);
    },
    CASE("numeral_alternatives(123)") {
        const auto actual = numeral_alternatives("123");
        const auto expected = vi{6, 15, 24, 123};
        EXPECT(actual == expected);
    },
    CASE("numeral_alternatives(111)") {
        const auto actual = numeral_alternatives("111");
        const auto expected = vi{3, 12, 111};
        EXPECT(actual == expected);
    },
    CASE("split_into_parts(abc)") {
        const auto actual = split_into_parts("abc");
        const auto expected = vector<string>{"abc"};
        EXPECT(actual == expected);
    },
    CASE("split_into_parts(333aaa22bb1c)") {
        const auto actual = split_into_parts("333aaa22bb1c");
        const auto expected = vector<string>{"333", "aaa", "22", "bb", "1", "c"};
        EXPECT(actual == expected);
    },
    CASE("part_selector(az)") {
        const auto actual = part_selector("az");
        const auto expected = vvi{{-97}, {-122}};
        EXPECT(actual == expected);
    },
    CASE("part_selector(24)") {
        const auto actual = part_selector("24");
        const auto expected = vvi{{6, 24}};
        EXPECT(actual == expected);
    },
    CASE("full_selector(12az1)") {
        const auto actual = full_selector("12az1");
        const auto expected = vvi{{3, 12}, {-97}, {-122}, {1}};
        EXPECT(actual == expected);
    },
    CASE("match_length(-97, 11, -97)") {
        const auto actual = match_length({-97, 11, -97});
        const auto expected = 13;
        EXPECT(actual == expected);
    },
    CASE("confirm_match positive A") {
        const auto actual = confirm_match({-97, 11, -97}, {-97, 12});
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("confirm_match positive B") {
        const auto actual = confirm_match({2, -100, 15}, {18});
        const auto expected = true;
        EXPECT(actual == expected);
    },
    CASE("confirm_match negative A") {
        const auto actual = confirm_match({11}, {2});
        const auto expected = false;
        EXPECT(actual == expected);
    },
    CASE("confirm_match negative B") {
        const auto actual = confirm_match({-100, -100}, {-100, -101});
        const auto expected = false;
        EXPECT(actual == expected);
    },
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
