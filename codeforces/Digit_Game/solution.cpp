#include <bits/stdc++.h>
using namespace std;

constexpr bool is_even(const char d) { return (d - '0') % 2 == 0; }
constexpr bool is_odd(const char d) { return (d - '0') % 2 != 0; }

int solve(const string &n) {
    const int sz = n.size();
    int odds_on_odd = 0;
    int evens_on_even = 0;

    for (int i = 1; i <= sz; ++i) {
        if (i % 2 && is_odd(n[i - 1])) ++odds_on_odd;
        if (i % 2 == 0 && is_even(n[i - 1])) ++evens_on_even;
    }

    if (sz % 2) { // Second ends
        return odds_on_odd > 0 ? 1 : 2;
    } else { // First ends
        return evens_on_even > 0 ? 2 : 1;
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int sz;
        cin >> sz;
        string n(sz, ' ');
        cin >> n;
        cout << solve(n) << '\n';
    }

    return 0;
}
