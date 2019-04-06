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
    int trap(const vector<int> &hs);
};

int Solution::trap(const vector<int> &hs) { return hs[0]; }

int main() {
    cout << Solution().trap({1, 2}) << endl;

    return 0;
}
