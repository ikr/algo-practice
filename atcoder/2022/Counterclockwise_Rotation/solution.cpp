#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr double PI = 3.14159265358979323846;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(7) << fixed;

    double a, b, d;
    cin >> a >> b >> d;

    const auto r = (2.0 * PI * d) / 360.0;

    const auto a_ = a * cos(r) - b * sin(r);
    const auto b_ = a * sin(r) + b * cos(r);

    cout << a_ << " " << b_ << '\n';
    return 0;
}
