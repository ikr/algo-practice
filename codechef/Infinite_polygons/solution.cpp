#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr double PI = 3.14159265358979323846;

double area(const double n, const double a) {
    return (n * a * a / 4.0) / tan(PI / n);
}

double ev_poly_num(const int n) {
    const double a1 = 10000.0;
    const double s1 = area(doof(n), a1);

    const double theta = (doof(n - 2) * PI / doof(n));
    const double a2 = a1 * sin(theta / 2.0);
    const double s2 = area(doof(n), a2);

    const double q = s2 / s1;
    assert(q < 1.0);

    return 1.0 / (1.0 - q);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(7) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << ev_poly_num(n) << '\n';
    }

    return 0;
}
