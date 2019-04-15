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
    return s == p;
}

int main() {
    cout << Solution().isMatch("acdcb", "a*c?b") << endl;

    return 0;
}
