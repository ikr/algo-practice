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
    int search(const vector<int> &xs, const int target) {
        return search(xs, 0, xs.size(), target);
    }

  private:
    int search(const vector<int> &xs, const int begin, const int end,
               const int target) {
        const int sz = end - begin;

        if (sz == 0)
            return -1;

        if (sz == 1)
            return xs[begin] == target ? begin : -1;

        const int mid{begin + sz / 2};

        if (is_ordered(xs, mid, end)) {
            if (xs[mid] <= target && target <= xs[end - 1])
                return search(xs, mid, end, target);

            return search(xs, begin, mid, target);
        }

        if (xs[begin] <= target && target <= xs[mid - 1])
            return search(xs, begin, mid, target);

        return search(xs, mid, end, target);
    }

    bool is_ordered(const vector<int> &xs, const int begin, const int end) {
        assert(end - begin > 0);

        if (end - begin == 1)
            return true;

        return xs[begin] < xs[end - 1];
    }
};

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (const T &x : xs) {
        os << x << ' ';
    }

    return os;
}

int main() {
    vector<int> xs{9, 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8};
    const int target = 0;

    cout << "xs are " << xs << "target is " << target << endl;
    cout << "result is " << Solution().search(xs, target) << endl;

    return 0;
}
