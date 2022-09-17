#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<ll> matching_ints(const ll X) {
    vector<int> os;
    for (int shift = 0; shift < 61; ++shift) {
        if ((1LL << shift) & X) {
            os.push_back(shift);
        }
    }
    assert(sz(os) < 16);

    vector<ll> result{0};

    for (int bits = 1; bits < (1 << sz(os)); ++bits) {
        ll Y{};

        for (int i = 0; i < sz(os); ++i) {
            if ((1 << i) & bits) {
                Y |= (1LL << os[i]);
            }
        }

        result.push_back(Y);
    }

    sort(begin(result), end(result));
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll X;
    cin >> X;

    for (const auto a : matching_ints(X)) {
        cout << a << '\n';
    }

    return 0;
}
