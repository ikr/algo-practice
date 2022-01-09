#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    set<int> ok{2, 3, 5};
    cout << (ok.count(t) ? "YES\n" : "NO\n") << '\n';

    return 0;
}
