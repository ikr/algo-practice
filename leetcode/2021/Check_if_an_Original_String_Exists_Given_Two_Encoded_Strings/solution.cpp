#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
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

using Quad = tuple<int, int, int, int>;

constexpr bool is_char(const vvi &sel, const int i) { return sel[i][0] < 0; }

bool confirm_related(const vvi &sel_a, const vvi &sel_b) {
    map<Quad, bool> memo;
    function<bool(pii, pii)> recur;
    recur = [&](const pii pa, const pii pb) -> bool {
        const auto [ia, oa] = pa;
        const auto [ib, ob] = pb;
        const Quad key{ia, oa, ib, ob};

        {
            const auto cache_it = memo.find(key);
            if (cache_it != cend(memo)) return cache_it->second;
        }

        if (ia == sz(sel_a) && ib == sz(sel_b)) {
            assert(!oa);
            assert(!ob);
            return memo[key] = true;
        }

        if ((ia == sz(sel_a)) != (ib == sz(sel_b))) {
            return memo[key] = false;
        }

        if (!oa) {

        } else {
            assert(!is_char(sel_a, ia));
        }
    };

    return recur({0, 0}, {0, 0});
}

struct Solution final {
    bool possiblyEquals(const string &a, const string &b) const {
        return confirm_related(full_selector(a), full_selector(b));
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
    CASE("Test case 7") {
        const auto actual = Solution{}.possiblyEquals("1", "z");
        const auto expected = true;
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
    CASE("Test case 124") {
        const auto actual = Solution{}.possiblyEquals(
            "v375v736v443v897v633v527v781v121v317", "475v899v753v784v438v415v431v216v968");
        const auto expected = false;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
