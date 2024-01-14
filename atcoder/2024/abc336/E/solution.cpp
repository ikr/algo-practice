#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

int digits_sum(ll n) {
    int ans{};
    while (n) {
        ans += inof(n % 10LL);
        n /= 10LL;
    }
    return ans;
}

ll brute_force(const ll n) {
    ll result{};
    for (ll i = 1; i <= n; ++i) {
        result += (i % digits_sum(i) == 0);
    }
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N;
    cin >> N;
    cout << brute_force(N) << '\n';
    return 0;
}
