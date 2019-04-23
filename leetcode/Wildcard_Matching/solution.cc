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

using Iter = std::string::const_reverse_iterator;

bool are_all_stars(Iter begin, Iter end) {
    return all_of(begin, end, [](const char c) { return c == '*'; });
}

bool is_alpha(const char c) { return c >= 'a' && c <= 'z'; }
bool is_wildcard(const char c) { return c == '*' || c == '?'; }

void set_result(vector<vector<bool>> &result, Iter plo, Iter phi, Iter slo,
                Iter shi, bool value) {
    assert(result.size() > 0);
    assert(distance(plo, phi) >= 0);
    assert(static_cast<size_t>(distance(plo, phi)) < result.size());
    assert(distance(slo, shi) >= 0);
    assert(static_cast<size_t>(distance(slo, shi)) < result[0].size());

    result[distance(plo, phi)][distance(slo, shi)] = value;
}

bool get_result(vector<vector<bool>> &result, Iter plo, Iter phi, Iter slo,
                Iter shi) {
    assert(result.size() > 0);
    assert(distance(plo, phi) >= 0);
    assert(static_cast<size_t>(distance(plo, phi)) < result.size());
    assert(distance(slo, shi) >= 0);
    assert(static_cast<size_t>(distance(slo, shi)) < result[0].size());

    return result[distance(plo, phi)][distance(slo, shi)];
}

bool Solution::isMatch(const string &s, const string &p) const {
    vector<vector<bool>> result(p.size(), vector(s.size(), false));

    const Iter pb = p.rbegin();
    const Iter pe = p.rend();

    const Iter sb = s.rbegin();
    const Iter se = s.rend();

    if (pb == pe && sb == se)
        return true;

    if (pb == pe && sb != se)
        return false;

    if (pb != pe && sb == se)
        return are_all_stars(pb, pe);

    assert(is_alpha(*pb) || is_wildcard(*pb));
    assert(is_alpha(*sb));

    if (is_alpha(*pb)) {
        if (*pb == *sb) {
            set_result(result, pb, pb, sb, sb, true);

            for (Iter pi = pb + 1; pi != pe && *pi == '*'; ++pi)
                set_result(result, pb, pi, sb, sb, true);
        }
    } else if (*pb == '?') {
        set_result(result, pb, pb, sb, sb, true);

        for (Iter pi = pb + 1; pi != pe && *pi == '*'; ++pi)
            set_result(result, pb, pi, sb, sb, true);
    } else {
        assert(*pb == '*');

        for (Iter si = sb; si != se; ++si)
            set_result(result, pb, pb, sb, si, true);

        Iter pi = pb;
        for (; pi != pe && *pi == '*'; ++pi)
            set_result(result, pb, pi, sb, sb, true);

        if (pi != pe && (*pi == *sb || *pi == '?')) {
            set_result(result, pb, pi, sb, sb, true);
            ++pi;
        }

        for (; pi != pe && *pi == '*'; ++pi)
            set_result(result, pb, pi, sb, sb, true);
    }

    for (Iter pi = pb + 1; pi != pe; ++pi)
        for (Iter si = sb + 1; si != se; ++si) {
            assert(is_alpha(*pi) || is_wildcard(*pi));
            assert(is_alpha(*si));

            if (is_alpha(*pi))
                set_result(result, pb, pi, sb, si,
                           *pi == *si &&
                               get_result(result, pb, pi - 1, sb, si - 1));
            else if (*pi == '?')
                set_result(result, pb, pi, sb, si,
                           get_result(result, pb, pi - 1, sb, si - 1));
            else {
                assert(*pi == '*');

                set_result(result, pb, pi, sb, si,
                           get_result(result, pb, pi, sb, si - 1) ||
                               get_result(result, pb, pi - 1, sb, si));
            }
        }

    return result[p.size() - 1][s.size() - 1];
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
        {"*a", "ab", false}};
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
