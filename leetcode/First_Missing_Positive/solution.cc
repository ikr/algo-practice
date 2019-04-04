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

int place_all_return_max(vector<int> &xs) {
    int max_x = numeric_limits<int>::min();

    for (int i = 0; i != static_cast<int>(xs.size()); ++i) {
        if (xs[i] >= 0) {
            if (xs[i] >= static_cast<int>(xs.size()))
                xs.resize(xs[i] + 1);

            swap(xs[i], xs[xs[i]]);
        }

        if (xs[i] > max_x)
            max_x = xs[i];
    }

    return max_x;
}

} // namespace

struct Solution {
    int firstMissingPositive(vector<int> &xs);
};

int Solution::firstMissingPositive(vector<int> &xs) {
    if (!xs.size())
        return 1;

    int max_x = place_all_return_max(xs);
    place_all_return_max(xs);

    for (int i = 1; i != static_cast<int>(xs.size()); ++i)
        if (xs[i] != i)
            return i;

    return max(1, max_x + 1);
}

int main() {
    vector<int> xs{1, 2, 0};
    cout << xs << "| " << Solution().firstMissingPositive(xs) << endl;

    xs = {3, 4, -1, 1};
    cout << xs << "| " << Solution().firstMissingPositive(xs) << endl;

    xs = {7, 8, 9, 11, 12};
    cout << xs << "| " << Solution().firstMissingPositive(xs) << endl;

    xs = {3, 2, 1, 6, 5, 4, 7, 9, 9, 9, 9, 8, 11, 12, 11, 11};
    cout << xs << "| " << Solution().firstMissingPositive(xs) << endl;

    return 0;
}
