#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int y;
    cin >> y;

    const auto leap = [y]() -> bool {
        if (y % 4) return false;
        if (y % 100) return true;
        return (y % 400) == 0;
    }();
    cout << (leap ? 366 : 365) << "\n";
    return 0;
}
