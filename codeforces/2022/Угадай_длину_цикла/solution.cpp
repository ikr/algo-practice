#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll query(const ll a, const ll b) {
    cout << "? " << a << ' ' << b << endl;
    ll result;
    cin >> result;
    return result;
}

void answer(const ll n) { cout << "! " << n << endl; }

void interact() {
    for (ll i = 1; i <= 25; ++i) {
        const auto a = query(i, i + 1);

        if (a == -1LL) {
            answer(i);
            return;
        }

        const auto b = query(i + 1, i);
        if (a != b) {
            answer(a + b);
            return;
        }
    }
}

int main() {
    interact();
    return 0;
}
