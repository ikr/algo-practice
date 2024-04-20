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

    unordered_map<ll, double> memo;

    const auto recur = [&](const auto self, const ll n) -> double {
        if (memo.contains(n)) return memo.at(n);
        return memo[n] = [&]() -> double {
            if (!n) return 0;
            const auto o1 = X + self(self, n / A);

            double o2 = 0;
            for (ll i = 2; i <= 6; ++i) o2 += self(self, n / i);
            o2 /= 5.0;
            o2 += 6 * Y / 5.0;

            return min(o1, o2);
        }();
    };

    cout << recur(recur, N) << '\n';
    return 0;
}
