#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace internal {
constexpr ll safe_mod(ll x, const ll m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

constexpr pair<ll, ll> inv_gcd(ll a, const ll b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};

    ll s = b, t = a;
    ll m0 = 0, m1 = 1;

    while (t) {
        const ll u = s / t;
        s -= t * u;
        m0 -= m1 * u;

        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }

    if (m0 < 0) m0 += b / s;
    return {s, m0};
}
} // namespace internal

constexpr ll inv_mod(const ll x, const ll m) {
    assert(1 <= m);
    const auto z = internal::inv_gcd(x, m);
    assert(z.first == 1);
    return z.second;
}

vector<int> cherry_indices(const vector<string> &rs) {
    vector<int> ans(rs.size());
    transform(rs.cbegin(), rs.cend(), ans.begin(),
              [](const string &r) -> int { return r.find('c'); });
    return ans;
}

int crt(const vector<int> a, const vector<int> p) { const int k = a.size(); }

struct SlotMachineHacking final {
    int win(const vector<string> &rs, vector<int> ss) const {
        const int n = rs.size();
        const auto cs = cherry_indices(rs);

        map<int, int> xs_by_p;

        for (int i = 0; i < n; ++i) {
            ss[i] %= rs[i].size();

            if (ss[i] == 0) {
                if (rs[i][0] != 'c') return -1;
            } else {
                if (__gcd(ss[i], static_cast<int>(rs[i].size())) != 1) {
                    return -1;
                }

                const int p = rs[i].size();
                const int x = (cs[i] * inv_mod(ss[i], p)) % p;

                if (xs_by_p.count(p)) {
                    if (xs_by_p.at(p) != x) return -1;
                } else {
                    xs_by_p[p] = x;
                }
            }
        }
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = SlotMachineHacking{}.win({"abc", "acb", "cab"}, {32, 31, 30});
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = SlotMachineHacking{}.win({"abc", "acb", "cab"}, {30, 33, 300000006});
        const auto expected = -1;
        EXPECT(actual == expected);
    },
    CASE("Example 2") {
        const auto actual = SlotMachineHacking{}.win({"abc", "bac", "abpc"}, {1, 1, 1});
        const auto expected = 10;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
