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

namespace {

vector<int> count_chars(const string &w) {
    vector<int> res('z' - 'a' + 1);

    for (const char c : w) {
        ++res[c - 'a'];
    }

    return res;
}

vector<char> common_chars(const vector<string> &ws) {
    vector<vector<int>> counts;

    for (const string &w : ws) {
        counts.push_back(count_chars(w));
    }

    vector<int> min_counts('z' - 'a' + 1, numeric_limits<int>::max());

    for (const auto &cc : counts) {
        for (size_t i = 0; i != cc.size(); ++i) {
            min_counts[i] = min(min_counts[i], cc[i]);
        }
    }

    vector<char> res;

    for (size_t i = 0; i != min_counts.size(); ++i) {
        for (int j = 0; j != min_counts[i]; ++j) {
            res.push_back(static_cast<char>('a' + i));
        }
    }

    return res;
}

} // namespace

struct Solution {
    vector<string> commonChars(const vector<string> &words);
};

vector<string> Solution::commonChars(const vector<string> &words) {
    const vector<char> cc = common_chars(words);
    vector<string> res(cc.size());

    for (size_t i = 0; i != cc.size(); ++i) {
        res[i] = string{cc[i]};
    }

    return res;
}

int main() {
    cout << Solution().commonChars({"bella", "label", "roller"}) << endl;

    return 0;
}
