#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

struct AlicesBirthday final {
    vi partition(const int k) const {
        function<vi(int)> recur;
        recur = [&recur](const int x) -> vi {
            if (x == 0) return {};
            if (x == 1) return {-1};
            if (x == 2) return {1};

            auto ans = recur(x - 3);
            if (ans == vi{-1}) return {-1};

            ans.push_back(x);
            return ans;
        };

        return recur(k);
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("K is 3") {
        const auto actual = AlicesBirthday{}.partition(3);
        const auto expected = vi{3};
        EXPECT(actual == expected);
    },
    CASE("K is 5") {
        const auto actual = AlicesBirthday{}.partition(5);
        const auto expected = vi{1, 5};
        EXPECT(actual == expected);
    },
    CASE("K is 1") {
        const auto actual = AlicesBirthday{}.partition(1);
        const auto expected = vi{-1};
        EXPECT(actual == expected);
    },
    CASE("K is 6") {
        const auto actual = AlicesBirthday{}.partition(6);
        const auto expected = vi{3, 6};
        EXPECT(actual == expected);
    },
    CASE("K is 7") {
        const auto actual = AlicesBirthday{}.partition(7);
        const auto expected = vi{-1};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
