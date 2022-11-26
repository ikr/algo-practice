#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

constexpr double time(const ll A, const ll B, const ll k) {
    return doof(B) * doof(k) + doof(A) / sqrt(1.0 + doof(k));
}

double shortest_time(const ll A, const ll B) {
    const auto x =
        pow(doof(A) * doof(A) / (4.0 * doof(B) * doof(B)), 1.0 / 3.0);
    const auto k = x - 1;
    const auto o1 = llof(k);
    const auto o2 = o1 + 1;

    return min(time(A, B, o1), time(A, B, o2));
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
