#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n, 0);
    for (auto &x : xs) cin >> x;

    if (n == 1) {
        cout << "EQUAL\n";
        return 0;
    }

    adjacent_difference(cbegin(xs), cend(xs), begin(xs));

    if (all_of(next(cbegin(xs)), cend(xs), [](const int x) { return x == 0; })) {
        cout << "EQUAL\n";
    } else if (all_of(next(cbegin(xs)), cend(xs), [](const int x) { return x >= 0; })) {
        cout << "NONDECREASING\n";
    } else if (all_of(next(cbegin(xs)), cend(xs), [](const int x) { return x <= 0; })) {
        cout << "NONINCREASING\n";
    } else {
        cout << "NONE\n";
    }

    return 0;
}
