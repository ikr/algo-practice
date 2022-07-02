#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using ll = long long;

static constexpr ll INF = 1e18;

template <typename T> struct mmin final {
    constexpr T operator()(const T &a, const T &b) const {
        return std::min(a, b);
    }
};

vector<ll> pref_sums(const vector<ll> &xs) {
    vector<ll> ss(sz(xs));
    partial_sum(cbegin(xs), cend(xs), begin(ss));
    return ss;
}

vector<ll> pref_mins(const vector<ll> &xs) {
    vector<ll> ss(sz(xs));
    partial_sum(cbegin(xs), cend(xs), begin(ss), mmin<ll>{});
    return ss;
}

ll min_total_time_of_repeats(const vector<ll> &A, const vector<ll> &B,
                             const ll X) {
    assert(sz(A) == sz(B));
    const auto sa = pref_sums(A);
    const auto sb = pref_sums(B);
    const auto mb = pref_mins(B);

    ll result = INF;

    for (int i = 0; i < min(sz(A), inof(X)); ++i) {
        const auto t_reach = sa[i] + sb[i];
        const auto t_rep = (X - i - 1 > 0LL) ? (X - i - 1) * mb[i] : 0LL;
        result = min(result, t_reach + t_rep);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, X;
    cin >> N >> X;

    vector<ll> A(N);
    vector<ll> B(N);

    for (int i = 0; i < N; ++i) {
        cin >> A[i] >> B[i];
    }

    cout << min_total_time_of_repeats(A, B, X) << '\n';
    return 0;
}
