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

int main() {
    cout << Solution().isMatch("acdcb", "a*c??b") << endl;

    return 0;
}
