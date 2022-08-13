#include "lest.hpp"
#include <atcoder/modint>
#include <bits/stdc++.h>

using namespace std;
using mint = atcoder::modint1000000007;

struct Fancy final {
    Fancy() : xs{}, A{1}, B{0} {}

    void append(const int x) { xs.push_back((mint{x} - B) * A.inv()); }

    void addAll(const int b) { B += b; }

    void multAll(const int a) {
        A *= a;
        B *= a;
    }

    int getIndex(const int i) const {
        return i < static_cast<int>(xs.size()) ? (A * xs[i] + B).val() : -1;
    }

  private:
    vector<mint> xs;
    mint A;
    mint B;
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        Fancy fancy;
        fancy.multAll(9890878);
        fancy.addAll(12329911);
        fancy.append(7);

        EXPECT(fancy.getIndex(0) == 7);
    },
    CASE("Example 1") {
        Fancy fancy;
        fancy.append(2);   // fancy sequence: [2]
        fancy.addAll(3);   // fancy sequence: [2+3] -> [5]
        fancy.append(7);   // fancy sequence: [5, 7]
        fancy.multAll(2);  // fancy sequence: [5*2, 7*2] -> [10, 14]

        EXPECT(fancy.getIndex(0) == 10);

        fancy.addAll(3);   // fancy sequence: [10+3, 14+3] -> [13, 17]
        fancy.append(10);  // fancy sequence: [13, 17, 10]
        fancy.multAll(2);  // fancy sequence: [13*2, 17*2, 10*2] -> [26, 34, 20]

        EXPECT(fancy.getIndex(0) == 26);
        EXPECT(fancy.getIndex(1) == 34);
        EXPECT(fancy.getIndex(2) == 20);
    },
    CASE("Example 12") {
        Fancy fancy;
        fancy.multAll(12);
        EXPECT(fancy.getIndex(0) == -1);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
