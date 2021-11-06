#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct NumArray final {
    NumArray(const vector<int> &xs) : prefix_sums(xs.size() + 1, 0) {
        int curr = 0;
        for (size_t i = 1; i <= xs.size(); ++i) {
            curr += xs[i - 1];
            prefix_sums[i] = curr;
        }
    }

    int sumRange(int i, int j) const {
        return prefix_sums[j + 1] - prefix_sums[i];
    }

  private:
    vector<int> prefix_sums;
};

// clang-format off
const lest::test tests[] = {
    CASE("1, 2, 3") {
        const NumArray s({1, 2, 3});
        const auto actual = s.sumRange(1, 2);
        const auto expected = 5;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
