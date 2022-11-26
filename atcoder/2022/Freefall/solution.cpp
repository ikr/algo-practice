#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

constexpr double time(const ll A, const ll B, const double k) {
    return doof(B) * k + doof(A) / sqrt(1.0 + k);
}

double shortest_time(const ll A, const ll B) {
    double lo = 0.0;
    double hi = doof(A);

    for (int i = 1; i <= 10000; ++i) {
        const auto mid = lo + (hi - lo) / 2.0;
        if (time(A, B, mid) >= time(A, B, lo)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }

    if (time(A, B, doof(llof(lo))) <= time(A, B, doof(llof(lo)) + 1.0)) {
        return time(A, B, doof(llof(lo)));
    }

    return time(A, B, doof(llof(lo)) + 1.0);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(7) << fixed;

    ll A, B;
    cin >> A >> B;

    cout << shortest_time(A, B) << '\n';
    return 0;
}
