#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll max_exp(const ll X, const ll Y, const ll A, const ll B) {
    ll ans = 0;

    ll x = X;
    while (log2(x) + log2(A) < log2(X + B) && log2(x) + log2(A) < log2(Y)) {
        x *= A;
        ++ans;
    }

    ans += (Y - x - 1) / B;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll X, Y, A, B;
    cin >> X >> Y >> A >> B;

    cout << max_exp(X, Y, A, B) << '\n';
    return 0;
}
