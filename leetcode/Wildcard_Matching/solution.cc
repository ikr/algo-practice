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

using Iter = std::string::const_iterator;

bool are_all_stars(Iter begin, Iter end) {
    return all_of(begin, end, [](const char c) { return c == '*'; });
}

bool is_alpha(const char c) { return c >= 'a' && c <= 'z'; }
bool is_wildcard(const char c) { return c == '*' || c == '?'; }

bool is_match(Iter pi, Iter pe, Iter si, Iter se) {
    if (pi == pe && si == se)
        return true;

    if (pi == pe && si != se)
        return false;

    if (pi != pe && si == se)
        return are_all_stars(pi, pe);

    assert(is_alpha(*pi) || is_wildcard(*pi));
    assert(is_alpha(*si));

    if (is_alpha(*pi))
        return *pi == *si && is_match(pi + 1, pe, si + 1, se);

    if (*pi == '?')
        return is_match(pi + 1, pe, si + 1, se);

    assert(*pi == '*');
    return is_match(pi, pe, si + 1, se) || is_match(pi + 1, pe, si, se);
}

bool Solution::isMatch(const string &s, const string &p) const {
    return is_match(p.begin(), p.end(), s.begin(), s.end());
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
        {"c*a*b", "aab", false}};
}

int main() {
    for (const TestCase &tc : test_cases()) {
        const bool result = Solution().isMatch(tc.candidate, tc.pattern);

        cout << '/' << tc.pattern << "/ on \"" << tc.candidate << "\" is "
             << result << endl;

        assert(result == tc.expected_result);
    }

    return 0;
}
