#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
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
    int divide(int p, int q) {
        const int r = div_positive(abs(p), abs(q));
        return changes_sign(p, q) ? -r : r;
    }

  private:
    static int div_positive(int p, int q) {
        assert(p >= 0);
        assert(q > 0);
        if (p < q || p - q < q)
            return 0;
        if (p == q)
            return 1;

        pair<int, int> fprod = closest_doubled(p, q);
        if (fprod.second == p)
            return fprod.first;
        assert(fprod.second < p);

        fprod = closest_incremented(p, q, fprod);
        return fprod.first;
    }

    static pair<int, int> closest_doubled(int target, int q) {
        assert(q < target);
        int factor = 1;
        int prod = q;

        while (true) {
            const int prod1 = prod + prod;
            if (prod1 > target)
                break;

            prod = prod1;
            factor = factor + factor;
        }

        return make_pair(factor, prod);
    }

    static pair<int, int>
    closest_incremented(int target, int q, const pair<int, int> &start_with) {
        int factor = start_with.first;
        int prod = start_with.second;

        while (true) {
            const int prod1 = prod + q;
            if (prod1 > target)
                break;

            prod = prod1;
            ++factor;
        }

        return make_pair(factor, prod);
    }

    static bool changes_sign(int p, int q) {
        return !(p == 0 || (p > 0 && q > 0) || (p < 0 && q < 0));
    }
};

ostream &operator<<(ostream &os, pair<int, int> p) {
    return os << '(' << p.first << ", " << p.second << ')';
}

int main() {
    const int dividend = 132431;
    const int divisor = 35;
    const int result = Solution().divide(dividend, divisor);

    cout << dividend << " / " << divisor << " = " << result << endl;

    return 0;
}
