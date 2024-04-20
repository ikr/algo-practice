#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static constexpr double Eps = 0.000000000000001;

template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(7) << fixed;

    ll N;
    cin >> N;

    int A;
    cin >> A;

    int X, Y;
    cin >> X >> Y;

    const auto recur = [&](const auto self, const double p0,
                           const ll n) -> double {
        if (!n || p0 < Eps) return 0;
        vector<double> o(7, 0);
        o[0] = X + self(self, p0, n / A);
        for (ll i = 1; i <= 6; ++i) {
            o[i] = Y + self(self, p0 / 6.0, n / i);
        }
        return p0 * (*min_element(cbegin(o), cend(o)));
    };

    cout << recur(recur, 1.0, N) << '\n';
    return 0;
}
