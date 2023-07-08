#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int A, B;
    cin >> A >> B;

    A--;
    B--;

    const auto yes = (B - A) == 1 && (A / 3 == B / 3);
    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
