#include <bits/stdc++.h>
using namespace std;

bool can_partition(vector<int> xs) {
    sort(begin(xs), end(xs));

    do {
        for (int i = 1; i <= 3; ++i) {
            const int x = accumulate(cbegin(xs), cbegin(xs) + i, 0);
            const int y = accumulate(cbegin(xs) + i, cend(xs), 0);
            if (x == y) return true;
        }
    } while (next_permutation(begin(xs), end(xs)));

    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int a, b, c, d;
    cin >> a >> b >> c >> d;

    const bool ans = can_partition({a, b, c, d});
    cout << (ans ? "Yes\n" : "No\n");

    return 0;
}
