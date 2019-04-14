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
    string multiply(const string &num1, const string &num2);
};

void multiply_digits(const size_t i, const int di, const size_t j, const int dj,
                     vector<int> &res) {
    const int d0 = dj * di % 10;
    const int d1 = dj * di / 10;
    const size_t out_idx = j + i;

    const int carry0 = (res[out_idx] + d0) / 10;
    res[out_idx] = (res[out_idx] + d0) % 10;

    const int carry1 = (res[out_idx + 1] + carry0 + d1) / 10;
    res[out_idx + 1] = (res[out_idx + 1] + carry0 + d1) % 10;

    int carry = carry1;
    size_t ii = out_idx + 2;

    for (;;) {
        res[ii] += carry;

        if (res[ii] > 9)
            res[ii] %= 10;
        else
            break;

        ++ii;
    }
}

string Solution::multiply(const string &num1, const string &num2) {
    return num1 + num2;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (T x : xs) {
        os << x << ' ';
    }

    return os;
}

int main() {
    vector<int> res(5, 0);
    multiply_digits(0, 9, 0, 9, res);
    cout << res << endl;

    cout << Solution().multiply("12", "34") << endl;

    return 0;
}
