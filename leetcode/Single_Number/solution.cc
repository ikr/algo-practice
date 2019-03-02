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
    int singleNumber(const vector<int> &xs) {
        int result{0};

        for (const int x: xs) {
            result ^= x;
        }

        return result;
    }
};

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (const T &x : xs) {
        os << x << ' ';
    }

    return os;
}

int main() {
    Solution s;
    vector<int> xs{4, 1, 2, 1, 2};

    cout << xs << endl;
    cout << s.singleNumber(xs) << endl;

    return 0;
}
