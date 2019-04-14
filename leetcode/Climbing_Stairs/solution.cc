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

struct Solution {
    int climbStairs(int n) const;
};

int Solution::climbStairs(int n) const {
    switch (n) {
    case 1:
        return 1;

    case 2:
        return 2;

    default:
        return climbStairs(n - 1) + climbStairs(n - 2);
    }
}

int main() {
    cout << Solution().climbStairs(18) << endl;
    cout << Solution().climbStairs(44) << endl;

    return 0;
}
