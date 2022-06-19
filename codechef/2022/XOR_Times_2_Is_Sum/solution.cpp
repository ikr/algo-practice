#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using ll = long long;

ll sought_pairs_num(const vector<ll> &A) {
    ll result{};

    for (int i = 0; i < sz(A) - 1; ++i) {
        for (int j = i + 1; j < sz(A); ++j) {
            if (2LL * (A[i] ^ A[j]) == A[i] + A[j]) ++result;
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<ll> A(N);
    for (auto &a : A) cin >> a;

    cout << sought_pairs_num(A) << '\n';

    return 0;
}
