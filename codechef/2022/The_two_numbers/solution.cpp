#include <iostream>
#include <numeric>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll f_max(const ll N) {
    auto result = N - 2;

    for (auto a = N / 2LL, b = N - a; a > 0; --a, ++b) {
        const auto g = gcd(a, b);

        if (g == 1) {
            result = max(result, (a * b) / g - g);
            break;
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;
        cout << f_max(N) << '\n';
    }

    return 0;
}
