#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Input final {
    vector<ll> A;
    vector<ll> D;
    vector<ll> TA;
    vector<ll> TD;
};

Input gen_input(const int P, const int T, const ll seed, const ll MP,
                const ll MT) {
    vector<ll> A(P);
    vector<ll> D(P);
    vector<ll> TA(T);
    vector<ll> TD(T);

    ll state = seed;

    for (int i = 0; i < P; ++i) {
        state = (state * 1103515245 + 12345) % (1LL << 31);
        A[i] = (state / 10LL) % MP;
        state = (state * 1103515245 + 12345) % (1LL << 31);
        D[i] = (state / 10LL) % MP;
    }

    for (int j = 0; j < T; ++j) {
        state = (state * 1103515245 + 12345) % (1LL << 31);
        TA[j] = (state / 10LL) % MT;
        state = (state * 1103515245 + 12345) % (1LL << 31);
        TD[j] = (state / 10LL) % MT;
    }

    return Input{A, D, TA, TD};
}

using tri = tuple<ll, ll, int>;

constexpr ll sq(const ll x) { return x * x; };

struct HockeyLeagueDraft final {
    int draft(const int P, const int T, const int seed, const int MP,
              const int MT) const {
        const auto in = gen_input(P, T, seed, MP, MT);

        multiset<tri> pqa;
        multiset<tri> pqd;

        for (int i = 0; i < P; ++i) {
            pqa.emplace(in.A[i], in.D[i], -i);
            pqd.emplace(in.D[i], in.A[i], -i);
        }

        for (int t = 0; t < T; ++t) {
            const auto i_a = -get<2>(*crbegin(pqa));
            const auto i_d = -get<2>(*crbegin(pqd));

            const auto o_a = sq(in.TA[t] + in.A[i_a]) + sq(in.TD[t]);
            const auto o_d = sq(in.TA[t]) + sq(in.TD[t] + in.D[i_d]);

            const auto i = [&]() -> int {
                if (o_a == o_d) {
                    if (i_a <= i_d) {
                        pqa.erase(tri{in.A[i_a], in.D[i_a], -i_a});
                        pqd.erase(tri{in.D[i_a], in.A[i_a], -i_a});
                        return i_a;
                    } else {
                        pqa.erase(tri{in.A[i_d], in.D[i_d], -i_d});
                        pqd.erase(tri{in.D[i_d], in.A[i_d], -i_d});
                        return i_d;
                    }
                } else if (o_a > o_d) {
                    pqa.erase(tri{in.A[i_a], in.D[i_a], -i_a});
                    pqd.erase(tri{in.D[i_a], in.A[i_a], -i_a});
                    return i_a;
                } else {
                    pqa.erase(tri{in.A[i_d], in.D[i_d], -i_d});
                    pqd.erase(tri{in.D[i_d], in.A[i_d], -i_d});
                    return i_d;
                }
            }();

            if (t == T - 1) {
                return i;
            }
        }

        assert(false && "/o\\");
        return -1;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = HockeyLeagueDraft{}.draft(5, 3, 47, 1000000, 10000000);
        const auto expected = 0;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = HockeyLeagueDraft{}.draft(12, 7, 42000, 100, 100);
        const auto expected = 2;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
