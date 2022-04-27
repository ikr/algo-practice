#include "lest.hpp"
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> constexpr typename T::const_iterator xbegin(const T &xs) {
    return xs.cbegin();
}

template <typename T> constexpr typename T::const_iterator xend(const T &xs) {
    return xs.cend();
}

struct TwoLineMinesweeper final {
    vector<string> solve(const vector<int> &xs) const {
        vector<string> result;

        function<void(string, int)> self;
        self = [&](string cur, const int i) -> void {
            if (sz(result) == 50) return;

            if (i == sz(xs)) {
                assert(sz(cur) == sz(xs));
                result.push_back(cur);
                return;
            }

            switch (xs[i]) {
            case 0:
                self(cur + "-", i + 1);
                break;

            case 1:
                if (!cur.empty()) {
                    if (cur.back() == '*') {
                        self(cur + "-", i + 1);
                    } else {
                        assert(cur.back() == '-');
                        if (i == sz(xs) - 1 || xs[i + 1] == 0) {
                            self(cur + "*", i + 1);
                        } else {
                            if (xs[i - 1] > 0) self(cur + "*-", i + 2);
                            if (xs[i + 1] > 0) self(cur + "-*", i + 2);
                        }
                    }
                } else {
                    assert(cur.empty());
                    if (i == sz(xs) - 1 || xs[i + 1] == 0) {
                        self(cur + "*", i + 1);
                    } else {
                        self(cur + "*-", i + 2);
                        self(cur + "-*", i + 2);
                    }
                }
                break;

            case 2:
                if (cur.empty()) {
                    self(cur + "**", i + 2);
                } else {
                    if (cur.back() == '*') {
                        if (i == sz(xs) - 1 || xs[i + 1] == 0) {
                            self(cur + "*", i + 1);
                        } else {
                            self(cur + "*-", i + 2);
                            self(cur + "-*", i + 2);
                        }
                    } else {
                        assert(cur.back() == '-');
                        if (i == sz(xs) - 1 || xs[i + 1] == 0) return;
                        self(cur + "**", i + 2);
                    }
                }
                break;

            case 3:
                if (cur.empty() || cur.back() != '*' || i == sz(xs) - 1) return;
                self(cur + "**", i + 2);
                break;

            default:
                assert(false && "/o\\");
            }
        };

        self("", 0);

        assert(!result.empty());
        assert(sz(result) <= 50);
        sort(begin(result), end(result));
        return result;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = TwoLineMinesweeper{}.solve({0, 0, 0, 0, 0, 0});
        const auto expected = vector<string>{"------" };
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = TwoLineMinesweeper{}.solve({0, 0, 1, 1, 1, 0});
        const auto expected = vector<string>{"---*--" };
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
