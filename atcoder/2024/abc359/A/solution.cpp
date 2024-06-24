#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<string> xs(n);
    for (auto &x : xs) {
        cin >> x;
    }

    cout << count(cbegin(xs), cend(xs), string{"Takahashi"}) << '\n';
    return 0;
}
