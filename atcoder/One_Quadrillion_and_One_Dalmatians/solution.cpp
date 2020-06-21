#include <bits/stdc++.h>
#include <climits>
using namespace std;
using ll = long long;
static const ll RADIX = 'z' - 'a' + 1;

string dog_name(ll n) {
    if (n < RADIX) return string(1, static_cast<char>('a' + n));

    return dog_name(n / RADIX - 1) +
           string(1, static_cast<char>('a' + (n % RADIX)));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll n;
    cin >> n;
    cout << dog_name(n - 1) << '\n';

    return 0;
}
