#include "lest.hpp"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }


template <typename T>
constexpr typename multiset<T>::const_iterator cbegin(const multiset<T> &xs) {
    return xs.cbegin();
}


template <typename T>
constexpr typename vector<T>::const_iterator cbegin(const vector<T> &xs) {
    return xs.cbegin();
}

template <typename T>
constexpr typename vector<T>::const_iterator cend(const vector<T> &xs) {
    return xs.cend();
}

string::const_iterator cbegin(const string &xs) { return xs.cbegin(); }
string::const_iterator cend(const string &xs) { return xs.cend(); }

struct Gym final {
    int calculateProfit(const int M, const int N, const int T) const {
        multiset<ll> leaves;
        int ans{};

        for (int i = 0; i < N; ++i) {
            const ll t = 2LL * i;
            while (!leaves.empty() && *cbegin(leaves) < t) {
                leaves.erase(cbegin(leaves));
            }

            assert(sz(leaves) <= M);
            if (sz(leaves) == M) continue;

            const ll duration = 1 + 2LL * ((llof(i) * llof(i)) % llof(T));
            leaves.insert(t + duration);
            ++ans;
        }

        return ans;
    }
};

// clang-format off
const lest::test tests[] = {
    CASE("Example 0") {
        const auto actual = Gym{}.calculateProfit(47, 10, 1000);
        const auto expected = 10;
        EXPECT(actual == expected);
    },
    CASE("Example 1") {
        const auto actual = Gym{}.calculateProfit(1, 10, 1000);
        const auto expected = 3;
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
