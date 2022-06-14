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

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

ll min_ops(const vector<ll> &A, const vector<ll> &ss, const ll X) {
    const auto it = lower_bound(cbegin(A), cend(A), X);

    if (it == cend(A)) {
        return sz(A) * X - ss.back();
    } else {
        const auto i = inof(distance(cbegin(A), it));

        ll result{};
        if (i > 0) {
            result += i * X - ss[i - 1];
        }

        result += (ss.back() - (i ? ss[i - 1] : 0LL)) - X * (sz(A) - i);

        return result;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, Q;
    cin >> N >> Q;

    vector<ll> A(N);
    for (auto &a : A) cin >> a;
    sort(begin(A), end(A));

    vector<ll> ss(N);
    partial_sum(cbegin(A), cend(A), begin(ss));

    for (int i = 1; i <= Q; ++i) {
        ll X;
        cin >> X;
        cout << min_ops(A, ss, X) << '\n';
    }

    return 0;
}
