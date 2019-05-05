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

namespace {
const size_t npos = string::npos;

bool all_stars(const string &s, const size_t from_idx) {
    assert(from_idx < s.size());

    return all_of(s.begin() + from_idx, s.end(),
                  [](const char c) { return c == '*'; });
}

size_t skip_to_last_star(const string &p, const size_t idx) {
    assert(idx < p.size());
    assert(p[idx] == '*');

    size_t i = idx;
    while (i + 1 != p.size() && p[i + 1] == '*') ++i;
    return i;
}
} // namespace

struct Solution {
    bool isMatch(const string &s, const string &p) const {
        const size_t psz = p.size();
        const size_t ssz = s.size();

        if (!psz && !ssz) return true;
        if (psz && !ssz) return all_stars(p, 0);
        if (!psz && ssz) return false;

        size_t i = 0;
        size_t j = 0;
        size_t psp_idx = npos;
        size_t psm_idx = npos;

        for (;;) {
            if (i == psz && j == ssz) return true;
            if (i == psz && j != ssz) return psp_idx != npos && p[i - 1] == '*';
            if (i != psz && j == ssz) return all_stars(p, i);

            if (p[i] == '*') {
                i = skip_to_last_star(p, i);
                psp_idx = ++i;
                psm_idx = npos;
                continue;
            }

            if (p[i] == '?' || p[i] == s[j]) {
                if (psp_idx != npos && psm_idx == npos) psm_idx = j;
                ++i;
                ++j;
                continue;
            }

            if (psp_idx == npos) return false;
            i = psp_idx;

            if (psm_idx != npos) {
                j = psm_idx + 1;
                psm_idx = npos;
            } else {
                ++j;
            }
        }
    }
};

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
        {"**f*", "g", false},
        {"foo?", "fooz", true},
        {"***?***?***", "ae", true},
        {"***?***?***", "a", false},
        {"solution*", "solutioncc", true},
        {"*s?", "scc", false},
        {"*tion*?", "solutionh", true},
        {"*tion*?*", "solutionh", true},
        {"*tion??*", "solutionh", false},
        {"*a", "ab", false},
        {"a*c*", "aba", false},
        {"*aba*aba*", "abaabbabab", true}};
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
