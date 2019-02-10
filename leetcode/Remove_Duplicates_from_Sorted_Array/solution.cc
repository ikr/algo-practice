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

class QuadraticSolution {
  public:
    int removeDuplicates(vector<int> &v) {
        if (v.size() < 2)
            return v.size();

        int shifts = 0;
        for (int i = v.size() - 2; i >= 0; --i) {
            if (v[i] == v[i + 1]) {
                shift_onto(v, v.size() - shifts, i);
                ++shifts;
            }
        }

        return v.size() - shifts;
    }

  private:
    static void shift_onto(vector<int> &v, int vsize, int k) {
        for (int i = k; i < vsize - 1; ++i) {
            v[i] = v[i + 1];
        }
    }
};

class Solution {
  public:
    int removeDuplicates(vector<int> &v) {
        if (v.size() < 2)
            return v.size();

        auto w = v.begin() + 1;
        auto r = v.begin() + 1;

        while (true) {
            while (*r == *(r - 1))
                ++r;

            if (r == v.end()) break;

            *w = *r;
            ++w;
            ++r;
        }

        return w - v.begin();
    }
};

ostream &operator<<(ostream &os, const vector<int> &v) {
    for (auto x : v) {
        os << x << ' ';
    }

    return os;
}

int main() {
    Solution s;
    vector<int> v{1, 1, 2};
    cout << v << endl;
    auto ret = s.removeDuplicates(v);

    cout << ret << endl;
    cout << v << endl;

    return 0;
}
