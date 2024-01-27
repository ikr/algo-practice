#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    const auto yes =
        isupper(xs[0]) && all_of(cbegin(xs) + 1, cend(xs),
                                 [](const char ch) { return islower(ch); });
    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
