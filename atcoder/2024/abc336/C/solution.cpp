#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static constexpr array Ds{'0', '2', '4', '6', '8'};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll N;
    cin >> N;
    --N;

    if (!N) {
        cout << '0' << '\n';
        return 0;
    }

    const ll b = ssize(Ds);
    string buf;
    while (N) {
        buf += Ds[N % b];
        N /= b;
    }
    reverse(begin(buf), end(buf));

    cout << buf << '\n';
    return 0;
}
