#include <bits/stdc++.h>
using namespace std;

int min_sides(int n) {
    const set<int> ex{2, 3, 5};
    return ex.count(n) ? 4 : 3;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    cout << min_sides(n) << '\n';

    return 0;
}
