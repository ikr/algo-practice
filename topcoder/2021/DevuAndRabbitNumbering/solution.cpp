#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

map<int, int> gather_freqs(const vi &xs) {
    map<int, int> ans;
    for (const auto x : xs) ++ans[x];
    return ans;
}

vector<pii> gather_kvs(const map<int, int> &xs) {
    return vector<pii>(xs.cbegin(), xs.cend());
}

static const string YES{"can"};
static const string NO{"cannot"};

struct DevuAndRabbitNumbering final {
    string canRenumber(const vi &xs) const {
        const auto ps = gather_kvs(gather_freqs(xs));
        if (ps[0].second > 3) return NO;

        const auto new_pre_without_overlap = [](const int x,
                                                const int f) -> int {
            assert(f > 0);
            if (f == 1) return x - 1;
            if (f == 2) return x;
            return x + 1;
        };

        int pre = new_pre_without_overlap(ps[0].first, ps[0].second);

        for (int i = 1; i < sz(ps); ++i) {
            const auto x = ps[i].first;
            const auto f = ps[i].second;

            if (x == pre) {
                if (f > 1) return NO;
                pre = x + 1;
                continue;
            }

            if (x - pre == 1) {
                if (f == 1) {
                    pre = x;
                } else if (f == 2) {
                    pre = x + 1;
                } else
                    return NO;

                continue;
            }

            if (f > 3) return NO;
            pre = new_pre_without_overlap(x, f);
        }

        return YES;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = DevuAndRabbitNumbering{}.canRenumber({1, 2, 3});
        const auto expected = YES;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = DevuAndRabbitNumbering{}.canRenumber({1, 2, 2});
        const auto expected = YES;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = DevuAndRabbitNumbering{}.canRenumber({2, 4, 2, 2, 1, 2});
        const auto expected = NO;
        EXPECT(actual == expected);
    },
    CASE("Example 3") {
        const auto actual = DevuAndRabbitNumbering{}.canRenumber({1, 2, 4, 2, 6, 6, 7});
        const auto expected = YES;
        EXPECT(actual == expected);
    },
    CASE("Example 4") {
        const auto actual = DevuAndRabbitNumbering{}.canRenumber({960,578,296,414,352,610,872,556,113,818,194,804,141,859,761,887,3,952,234,667,196,693,783});
        const auto expected = YES;
        EXPECT(actual == expected);
    },
    CASE("Example 5") {
        const auto actual = DevuAndRabbitNumbering{}.canRenumber({97, 64, 22, 17, 75, 97, 85, 68, 35, 82, 64, 10, 71, 11, 64, 64, 94, 52, 28, 40, 48, 46, 5, 82, 39, 65, 2, 93, 43, 50, 44, 90, 69, 72, 94, 6, 62, 17, 12, 12, 84, 33, 38});
        const auto expected = NO;
        EXPECT(actual == expected);
    },
    CASE("Own sample A") {
        const auto actual = DevuAndRabbitNumbering{}.canRenumber({1, 1, 1, 1});
        const auto expected = NO;
        EXPECT(actual == expected);
    },
    CASE("Own sample B") {
        const auto actual = DevuAndRabbitNumbering{}.canRenumber({1, 1, 1});
        const auto expected = YES;
        EXPECT(actual == expected);
    },
    CASE("Own sample C") {
        const auto actual = DevuAndRabbitNumbering{}.canRenumber({1, 1, 1, 2, 2});
        const auto expected = NO;
        EXPECT(actual == expected);
    },
    CASE("Own sample D") {
        const auto actual = DevuAndRabbitNumbering{}.canRenumber({2, 2, 2, 3});
        const auto expected = YES;
        EXPECT(actual == expected);
    },
    CASE("Hm…") {
        const auto actual = DevuAndRabbitNumbering{}.canRenumber({1, 1, 2, 3, 3});
        const auto expected = YES;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
