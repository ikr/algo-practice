#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int nice_staircases(ll x) {
    ll power = 1;
    int ans = 0;

    const auto the_n = [&]() { return (1LL << power) - 1LL; };
    const auto the_s = [&]() {
        const ll n = the_n();
        return (n * n + n) / 2LL;
    };

    while (the_s() <= x) {
        x -= the_s();
        ++ans;
        ++power;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        ll x;
        cin >> x;
        cout << nice_staircases(x) << '\n';
    }

    return 0;
}
