#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <locale>
#include <numeric>
#include <optional>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

struct Solution {
    bool isMatch(const string &s, const string &p) const;
};

bool Solution::isMatch(const string &s, const string &p) const {
    const size_t npos = string::npos;

    if (!p.size() && !s.size())
        return true;
    if (p.size() && !s.size())
        return all_stars(p);
    if (!p.size() && s.size())
        return false;

    size_t i = 0;
    size_t j = npos;
    size_t star_idx = npos;

    for (;;) {
        if (i == p.size())
            return j == s.size();

        if (p[i] == '*') {
            i = skip_to_last_star(p, i);
            star_idx = i;
            ++i;
            continue;
        }

        if (star_idx != npos) {
            while (j != s.size() && !(p[i] == '?' || p[i] == s[j]))
                ++j;

            if (j == s.size())
                return false;

            star_idx = npos;
            ++i;
            ++j;
            continue;
        }

        if (j == s.size())
            return false;

        if (p[j] == '?' || p[i] == s[j]) {
            ++i;
            ++j;
            continue;
        }

        return false;
    }
}

struct TestCase {
    string pattern;
    string candidate;
    bool expected_result;

    TestCase() : pattern{}, candidate{}, expected_result(true) {}
    ~TestCase() {}

    TestCase(const char *p, const char *s, bool r)
        : pattern{p}, candidate{s}, expected_result{r} {}
};

vector<TestCase> test_cases() {
    return {
        {"", "", true},
        {"a", "", false},
        {"", "a", false},
        {"a", "aa", false},
        {"z", "z", true},
        {"*", "aa", true},
        {"?a", "cb", false},
        {"*a*b", "adceb", true},
        {"a*c?b", "acdcb", false},
        {"a*c??b", "acdcb", true},
        {"abcd*zzz", "abcdzzz", true},
        {"a?cd*z?z", "aocdooooooooooooooooooooooooooooooooooooozzz", true},
        {"a?cd*z?z", "aacdcdooooooooooooozz", false},
        {"ab*cd*ok", "abocodook", false},
        {"*aab", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", true},
        {"?b*d**", "abed", true},
        {"?b*d**?", "abed", false},
        {"c*a*b", "aab", false},
        {"*b*", "b", true},
        {"*?****", "", false},
        {"*?****", "x", true},
        {"*?", "x", true},
        {"*??*", "x", false},
        {"****f***", "g", false},
        {"foo?", "fooz", true},
        {"***?***?***", "ae", true},
        {"***?***?***", "a", false},
        {"solution*", "solutioncc", true},
        {"*solution?", "solutioncc", false},
        {"*tion*?", "solutionh", true},
        {"*tion*?*", "solutionh", true},
        {"*tion??*", "solutionh", false},
        {"*a", "ab", false},
        {"a*c*", "aba", false}};
}

int main() {
    size_t x{string::npos};
    cout << x << endl;

    for (const TestCase &tc : test_cases()) {
        const bool result = Solution().isMatch(tc.candidate, tc.pattern);

        cout << '/' << tc.pattern << "/ on \"" << tc.candidate << "\" is "
             << result << endl;

        assert(result == tc.expected_result);
    }

    return 0;
}
