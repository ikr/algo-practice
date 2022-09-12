#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    ll res{};
    ll lo = 3, hi = llof(1e18);

    cout << "? 1 " << hi << endl;
    cin >> res;

    if (res != -1LL) {
        cout << "! " << hi << endl;
        return 0;
    }

    while (lo + 1 < hi) {
        const auto mid = lo + (hi - lo) / 2LL;
        cout << "? 1 " << mid << endl;

        cin >> res;

        if (res == -1LL) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    cout << "! " << lo << endl;
    return 0;
}
