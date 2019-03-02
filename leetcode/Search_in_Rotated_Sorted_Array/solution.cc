#include <algorithm>
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

class Solution {
  public:
    int search(const vector<int> &xs, int target) { return -1; }
};

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (const T &x : xs) {
        os << x << ' ';
    }

    return os;
}

int main() {
    vector<int> xs{4, 5, 6, 7, 0, 1, 2};
    const int target = 0;

    cout << "xs are " << xs << "target is " << target << endl;
    cout << Solution().search(xs, target) << endl;

    return 0;
}
