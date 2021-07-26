#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, x;
    cin >> n >> x;
    string s(n, ' ');
    cin >> s;

    for (const auto a : s) {
        if (a == 'x') {
            if (x > 0) --x;
            continue;
        }

        ++x;
    }

    cout << x << '\n';

    return 0;
}
