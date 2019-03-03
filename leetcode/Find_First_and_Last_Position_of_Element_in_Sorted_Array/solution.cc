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
    vector<int> searchRange(const vector<int> &xs, const int target) {
        const int sz = xs.size();

        if (!sz || !binary_search(xs.begin(), xs.end(), target))
            return {-1, -1};

        const int lo = xs[0] == target ? 0 : search_lo(xs, 0, sz, target);

        const int hi =
            xs.back() == target ? sz - 1 : search_hi(xs, 0, sz, target);

        return {lo, hi};
    }

  private:
    static int search_lo(const vector<int> &xs, const int begin, const int end,
                         const int target) {
        assert(xs[begin] < target);
        const int sz = end - begin;
        assert(sz > 1);
        const int mid = begin + (sz % 2 ? sz / 2 + 1 : sz / 2);

        if (xs[mid] == target && xs[mid - 1] < target)
            return mid;

        if (xs[mid] >= target)
            return search_lo(xs, begin, mid, target);

        return search_lo(xs, mid, end, target);
    }

    static int search_hi(const vector<int> &xs, const int begin, const int end,
                         const int target) {
        assert(xs[end - 1] > target);
        const int sz = end - begin;
        assert(sz > 1);
        const int mid = begin + (sz % 2 ? sz / 2 + 1 : sz / 2);

        if (xs[mid - 1] == target && xs[mid] > target)
            return mid - 1;

        if (xs[mid - 1] <= target)
            return search_hi(xs, mid, end, target);

        return search_hi(xs, begin, mid, target);
    }
};

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (const T &x : xs) {
        os << x << ' ';
    }

    return os;
}

int main() {
    vector<int> xs{7, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10};

    cout << xs << endl;
    cout << Solution().searchRange(xs, 7) << endl;

    return 0;
}
