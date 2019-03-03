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
    int searchInsert(const vector<int> &xs, const int target) {
        return find_insertion_idx(xs, 0, xs.size(), target);
    }

  private:
    int find_insertion_idx(const vector<int> &xs, const int begin,
                           const int end, const int target) {
        const int sz = end - begin;

        if (!sz)
            return -1;

        if (target < xs[begin])
            return begin;

        if (xs[end - 1] < target)
            return end;

        if (sz == 1)
            return xs[begin] == target ? begin : -1;

        const int mid = begin + (sz % 2 ? sz / 2 + 1 : sz / 2);

        if (xs[mid - 1] < target && xs[mid] > target)
            return mid;

        if (xs[mid] <= target)
            return find_insertion_idx(xs, mid, end, target);

        return find_insertion_idx(xs, begin, mid, target);
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
    const vector<int> xs{1,3,4,6};
    const int target = 5;

    cout << "xs are " << xs << "target is " << target << endl;
    cout << s.searchInsert(xs, 5) << endl;

    return 0;
}
