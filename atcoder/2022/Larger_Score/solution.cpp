#include <iostream>
#include <map>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

map<int, int> lowest_indices_by_x(const int lo, const vector<int> &xs) {
    map<int, int> result;
    for (int i = lo; i < sz(xs); ++i) {
        if (result.count(xs[i])) continue;
        result.emplace(xs[i], i);
    }
    return result;
}

static constexpr int INF = 1'000'000'000;

int min_ops(const vector<int> &A, const int K) {
    const auto idx = lowest_indices_by_x(K, A);
    int result = INF;

    for (int i = 0; i < K; ++i) {
        const auto it = idx.upper_bound(A[i]);
        if (it == cend(idx)) continue;
        result = min(result, it->second - i);
    }

    return result >= INF ? -1 : result;
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
