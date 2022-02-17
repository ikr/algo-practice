#include <bitset>
#include <cassert>
#include <climits>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

static constexpr int BITS_NAX = 10;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

set<int> to_set_of_bits(const vector<string> &xss) {
    set<int> result;
    for (const auto &xs : xss) {
        bitset<BITS_NAX> bits(xs);
        result.insert(inof(bits.to_ulong()));
    }
    return result;
}

int min_complaints(const vector<string> &preferences,
                   const vector<string> &forbidden) {
    const auto P = sz(preferences[0]);
    const auto fs = to_set_of_bits(forbidden);
    int result = INT_MAX;

    for (int x = 0; x < (1 << P); ++x) {
        if (fs.count(x)) continue;

        int curr{};
        for (const auto &p : preferences) {
            bitset<BITS_NAX> bits(p);
            curr += __builtin_popcount(inof(bits.to_ulong()) ^ x);
        }

        result = min(result, curr);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, M, P;
        cin >> N >> M >> P;
        assert(P <= BITS_NAX);

        vector<string> preferences(N);
        for (auto &p : preferences) {
            cin >> p;
            assert(sz(p) == P);
        }

        vector<string> forbidden(M);
        for (auto &f : forbidden) {
            cin >> f;
            assert(sz(f) == P);
        }

        cout << "Case #" << i << ": " << min_complaints(preferences, forbidden)
             << '\n';
    }

    return 0;
}
