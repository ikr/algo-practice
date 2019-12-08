#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

constexpr bool is_digit(const char c) { return '0' <= c && c <= '9'; }

string repeat(std::string str, const int n) {
    if (!n) {
        str.clear();
        return str;
    }

    if (n == 1 || str.empty()) return str;

    const auto period = str.size();

    if (period == 1) {
        str.append(n - 1, str.front());
        return str;
    }

    str.reserve(period * n);
    int m{2};
    for (; m < n; m *= 2) str += str;
    str.append(str.c_str(), (n - (m / 2)) * period);

    return str;
}

int read_rep_times(string::const_iterator &it) {
    stringstream ss;

    while (*it != '[') {
        ss << *it;
        ++it;
    }

    ++it;
    return stoi(ss.str());
}

string read_expr(string::const_iterator &it) {
    const int times = read_rep_times(it);
    stringstream ss;

    while (*it != ']') {
        if (is_digit(*it))
            ss << read_expr(it);
        else {
            ss << *it;
            ++it;
        }
    }

    ++it;
    return repeat(ss.str(), times);
}

struct Solution final {
    string decodeString(const string &source) const {
        string expr = "1[" + source + "]";
        auto it = expr.cbegin();
        return read_expr(it);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Problem statement example 1") {
        const auto actual = Solution().decodeString("3[a]2[bc]");
        const auto expected = "aaabcbc";
        EXPECT(actual == expected);
    },
    CASE("Problem statement example 2") {
        const auto actual = Solution().decodeString("3[a2[c]]");
        const auto expected = "accaccacc";
        EXPECT(actual == expected);
    },
    CASE("Problem statement example 3") {
        const auto actual = Solution().decodeString("2[abc]3[cd]ef");
        const auto expected = "abcabccdcdcdef";
        EXPECT(actual == expected);
    },
    CASE("degenerate 1") {
        const auto actual = Solution().decodeString("");
        const auto expected = "";
        EXPECT(actual == expected);
    },
    CASE("degenerate 2") {
        const auto actual = Solution().decodeString("0[abc]");
        const auto expected = "";
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
