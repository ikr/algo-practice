#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N, K;
    cin >> N >> K;

    const auto a = N / (K - 1);
    const auto b = a * K;

    cout << b << ' ' << a << '\n';
    return 0;
}
