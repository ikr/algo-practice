#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    vector<int> xs(8);
    for (auto &x : xs) cin >> x;

    const auto yes = is_sorted(cbegin(xs), cend(xs)) &&
                     all_of(cbegin(xs), cend(xs), [](const auto x) {
                         return 100 <= x && x <= 675 && (x % 25) == 0;
                     });

    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
