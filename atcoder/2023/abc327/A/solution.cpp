#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    string xs;
    cin >> xs;

    const auto yes =
        (xs.find("ab") != string::npos) || (xs.find("ba") != string::npos);
    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
