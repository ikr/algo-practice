#include <bits/stdc++.h>

using namespace std;

int main() {
    size_t fund1;
    size_t fund2;
    size_t price;

    cin >> fund1 >> fund2 >> price;

    const size_t missing1 = price - (fund1 % price);
    const size_t missing2 = price - (fund2 % price);

    const size_t extra1 = fund1 % price;
    const size_t extra2 = fund2 % price;

    const bool can_credit =
        (extra1 && missing2 <= extra1) || (extra2 && missing1 <= extra2);

    const size_t credit = can_credit ? min(missing1, missing2) : 0;

    cout << (fund1 / price + fund2 / price + (can_credit ? 1 : 0)) << ' '
         << credit << '\n';
}
