#include "lest.hpp"
#include <algorithm>
#include <array>
#include <atcoder/lazysegtree>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <optional>
#include <utility>
using namespace std;

using S = int;
using F = int;
constexpr S op(const S x, const S y) { return x + y; }
constexpr S e() { return 0; }
constexpr S mapping(const F f, const S x) { return max(f, x); }
constexpr F composition(const F f, const F g) { return max(f, g); }
constexpr F id() { return 0; }
using SegTree = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
using pii = pair<int, int>;
static constexpr int X_MAX = 1'000'000'000;

optional<pii> intersection(const pii ab1, const pii ab2) {
    const auto [a1, b1] = ab1;
    assert(a1 <= b1);
    const auto [a2, b2] = ab2;
    assert(a2 <= b2);
    if (b1 < a2 || b2 < a1) return nullopt;

    array<int, 4> xs{a1, a2, b1, b2};
    sort(begin(xs), end(xs));
    return pii{xs[1], xs[2]};
}

struct CountIntervals final {
    void add(const int a, const int b) {
        assert(a <= b);
        if (a == X_MAX || b == X_MAX) max_x_set = true;

        const auto chunk = X_MAX / 10;
        for (int i = 0; i <= 9; ++i) {
            const auto offset = i * chunk;
            const auto xaxb =
                intersection({a - offset, b - offset}, {0, chunk - 1});

            if (xaxb) {
                ensure_tree_init(i);
                const auto [xa, xb] = *xaxb;
                cerr << "xa:" << xa << " xb:" << xb << endl;
                trees[i]->apply(xa, xb + 1, 1);
            }
        }
    }

    int count() {
        return transform_reduce(
                   begin(trees), end(trees), 0, plus<int>{},
                   [](auto &pt) -> int { return pt ? pt->all_prod() : 0; }) +
               (max_x_set ? 1 : 0);
    }

    CountIntervals() : trees{}, max_x_set{false} {}

  private:
    void ensure_tree_init(const int i) {
        if (!trees[i]) trees[i] = SegTree(X_MAX / 10);
    }

    array<optional<SegTree>, 10> trees;
    bool max_x_set;
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 1") {
        CountIntervals ci;
        ci.add(2, 3);
        ci.add(7, 10);
        EXPECT(6 == ci.count());
        ci.add(5, 8);
        EXPECT(8 == ci.count());
    },
    CASE("Example A") {
        CountIntervals ci;
        ci.add(1, 1'000'000'000);
        ci.add(100'000'000 / 2, 100'000'000 + 100'000'000 / 2);
        EXPECT(1'000'000'000 == ci.count());
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
