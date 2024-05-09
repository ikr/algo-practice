#include <bits/stdc++.h>
using namespace std;

using ll = long long;

using lll = __int128_t;
using ulll = __uint128_t;

ostream &operator<<(ostream &dest, const lll value) {
    ostream::sentry s(dest);
    if (s) {
        ulll tmp = value < 0 ? -value : value;
        char buffer[128];
        char *d = end(buffer);

        do {
            --d;
            *d = "0123456789"[tmp % 10];
            tmp /= 10;
        } while (tmp != 0);

        if (value < 0) {
            --d;
            *d = '-';
        }

        const int len = static_cast<int>(end(buffer) - d);
        if (dest.rdbuf()->sputn(d, len) != len) dest.setstate(ios_base::badbit);
    }
    return dest;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll n_;
    cin >> n_;

    const lll n = n_;

    const auto total = n * n * (1 + n * n) / 2LL;
    const auto line = total / n;
    cout << line << '\n';
    return 0;
}
