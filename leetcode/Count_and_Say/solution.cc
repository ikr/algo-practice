#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
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
    string countAndSay(int n) const;
    static string next(const string &xs);
};

string Solution::countAndSay(int n) const { return to_string(n); }

string Solution::next(const string &xs) {
    if (xs.empty())
        return "1";

    char x = xs[0];
    int xlength = 1;
    string result;

    for (size_t i = 1; i != xs.size(); ++i) {
        const char y = xs[i];

        if (y == x) {
            ++xlength;
            continue;
        }

        result += to_string(xlength);
        result += x;

        xlength = 1;
        x = y;
    }

    result += to_string(xlength);
    result += x;

    return result;
}

int main() {
    cout << Solution().next("1113213211") << endl;

    return 0;
}
