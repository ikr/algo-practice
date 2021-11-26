#include <bits/stdc++.h>
using namespace std;

constexpr int max_teams(const int a, const int b) {
    return min({(a + b) / 4, a, b});
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;

        cout << max_teams(a, b) << '\n';
    }

    return 0;
}
