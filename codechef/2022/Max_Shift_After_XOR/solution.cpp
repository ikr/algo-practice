#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int prefix_xor_distinct_count(vector<ll> xs) {
    partial_sum(cbegin(xs), cend(xs), begin(xs),
                [](const ll agg, const ll x) -> ll { return agg ^ x; });
    return sz(set(cbegin(xs), cend(xs)));
}

int max_distinct_count(const vector<ll> &A) {
    int result{};

    for (int i = 0; i < sz(A); ++i) {
        auto xs = A;
        rotate(begin(xs), next(begin(xs), i), end(xs));
        result = max(result, prefix_xor_distinct_count(xs));
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        vector<ll> A(N);
        for (auto &a : A) cin >> a;

        cout << max_distinct_count(A) << '\n';
    }

    return 0;
}
