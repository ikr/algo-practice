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

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (T x : xs) {
        os << x << ' ';
    }

    return os;
}

using vec = vector<string>;

struct Solution {
    vec commonChars(const vec &words);
};

vec Solution::commonChars(const vec &words) { return words; }

int main() {
    cout << Solution().commonChars({"bella", "label", "roller"}) << endl;

    return 0;
}
