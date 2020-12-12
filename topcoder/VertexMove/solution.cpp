#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

struct VertexMove final {
    double largestTriangleArea(const int a0, const int b0, const int c0) const {
        vector<int> sides{a0, b0, c0};
        sort(begin(sides), end(sides));

        const double a = sides[0];
        const double b = sides[1];
        const double c = sides[2];

        const double x = (a * a + c * c - b * b) / (2.0 * c);
        const double y = sqrt(a * a - x * x);
        return c * (y + 1.0) / 2.0;
    }
};
// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = VertexMove{}.largestTriangleArea(3, 4, 5);
        const auto expected = 8.5;
        EXPECT(abs(actual - expected) < 0.000001);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
