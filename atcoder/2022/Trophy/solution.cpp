#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using ll = long long;

static constexpr ll INF = 2000000000LL * 1000000000LL;

vector<ll> pref_sums(const vector<ll> &xs) {
    vector<ll> ss(sz(xs));
    partial_sum(cbegin(xs), cend(xs), begin(ss));
    return ss;
}

ll min_total_time_of_repeats(const vector<ll> &A, const vector<ll> &B,
                             const ll X) {
    assert(sz(A) == sz(B));
    const auto sa = pref_sums(A);
    const auto sb = pref_sums(B);

    ll result = INF;

    for (int i = 0; i < min(sz(A), inof(X)); ++i) {
        const auto t_reach = sa[i] + sb[i];
        const auto t_rep = (X - i - 1LL) * B[i];
        result = min(result, t_reach + t_rep);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    ll X;
    cin >> N >> X;

    vector<ll> A(N, 0);
    vector<ll> B(N, 0);

    for (int i = 0; i < N; ++i) {
        cin >> A[i] >> B[i];
    }

    cout << min_total_time_of_repeats(A, B, X) << '\n';
    return 0;
}
