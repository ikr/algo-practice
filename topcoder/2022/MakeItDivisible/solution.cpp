#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

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

template <typename T> vi digits_reversed(T n) {
    vi ans;

    while (n) {
        ans.push_back(inof(n % static_cast<T>(10)));
        n /= static_cast<T>(10);
    }

    return ans;
}

template <typename T> vi digits(T n) {
    vi ans = digits_reversed(n);
    reverse(begin(ans), end(ans));
    return ans;
}

template <typename T> T number(const vi &ds) {
    if (ds.empty()) return 0;

    T ans = 0;
    T mul = 1;
    for (auto it = ds.crbegin(); it != ds.crend(); ++it) {
        ans += (*it) * mul;
        mul *= static_cast<T>(10);
    }
    return ans;
}

struct MakeItDivisible final {
    int change(const int n) const {
        if (n % 7 == 0) return n;
        auto ds = digits(n);

        for (int i = sz(ds) - 1; i >= 0; --i) {
            for (int x = (i ? 0 : 1); x <= 9; ++x) {
                ds[i] = x;

                const auto m = number<int>(ds);
                if (m % 7 == 0) return m;
            }
        }

        assert(false && "/o\\");
        return 0;
    }
};

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = MakeItDivisible{}.change(7028);
        const auto expected = 7028;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = MakeItDivisible{}.change(1111);
        const auto expected = 1113;
        EXPECT(actual == expected);
    },
    CASE("Example A") {

        for (int x = 100000000; x <= 999999999; ++x) {
            const auto ans = digits(MakeItDivisible{}.change(x));
            const auto ds = digits(x);

            EXPECT(sz(ans) == sz(ds));

            if (sz(ds) > 1) {
                EXPECT(ds[0] != 0);
            }

            int diffs{};
            for (int i = 0; i < sz(ds); ++i) {
                if (ans[i] != ds[i]) ++diffs;
            }

            if (diffs > 1) {
                cerr << ds << " " << ans << endl;
            }

            EXPECT(diffs <= 1);
        }
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
