#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static constexpr double Eps = 0.000001;

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(7) << fixed;

    ll N;
    cin >> N;

    ll A;
    cin >> A;

    double X, Y;
    cin >> X >> Y;

    const auto recur = [&](const auto self, const double p0,
                           const ll n) -> double {
        if (!n || p0 < Eps) return 0;
        const auto o0 = X + self(self, p0, n / A);
        vector<double> es(7, 0);
        for (ll i = 1; i <= 6; ++i) {
            es[i] = Y / 6.0 + self(self, p0 / 6.0, n / i) / 6.0;
        }
        const auto o1 = accumulate(cbegin(es), cend(es), 0.0);
        return p0 * min(o0, o1);
    };

    cout << recur(recur, 1.0, N) << '\n';
    return 0;
}
