#include <bits/stdc++.h>

using namespace std;

using ull_t = unsigned long long;

int main() {
    ull_t fund1;
    ull_t fund2;
    ull_t price;

    cin >> fund1 >> fund2 >> price;

    const ull_t missing1 = price - (fund1 % price);
    const ull_t missing2 = price - (fund2 % price);

    const ull_t extra1 = fund1 % price;
    const ull_t extra2 = fund2 % price;

    const bool can_credit =
        (extra1 && missing2 <= extra1) || (extra2 && missing1 <= extra2);

    const ull_t credit = can_credit ? min(missing1, missing2) : 0;

    cout << (fund1 / price + fund2 / price + (can_credit ? 1 : 0)) << ' '
         << credit << '\n';
}
