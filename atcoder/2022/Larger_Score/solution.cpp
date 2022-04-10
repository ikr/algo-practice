#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int INF = 1'000'000'000;

template <typename T> struct mmax final {
    constexpr T operator()(const T &a, const T &b) const {
        return std::max(a, b);
    }
};

int min_ops(const vector<int> &A, const int K) {
    vector<int> hi(sz(A), -1);
    partial_sum(cbegin(A) + K, cend(A), begin(hi) + K, mmax<int>{});
    int result = INF;

    for (int i = 0; i < K; ++i) {
        const auto jt = upper_bound(cbegin(hi), cend(hi), A[i]);
        if (jt == cend(hi)) continue;
        const auto j = inof(distance(cbegin(hi), jt));
        result = min(result, j - i);
    }

    return result == INF ? -1 : result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    cout << min_ops(A, K) << '\n';
    return 0;
}
