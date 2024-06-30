#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    const auto ir = xs.find('R');
    const auto im = xs.find('M');
    const auto yes = ir < im;

    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
