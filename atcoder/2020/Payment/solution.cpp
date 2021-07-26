#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    cout << (1000 - t % 1000) % 1000 << '\n';

    return 0;
}
