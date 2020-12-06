#include <bits/stdc++.h>
using namespace std;

vector<int> find_swapups(const vector<int> &xs) { return xs; }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n, 0);
    for (auto &x : xs) {
        cin >> x;
        --x;
    }

    const auto swapups = find_swapups(xs);
    if (swapups.empty()) {
        cout << "-1\n";
    } else {
        for (const auto x : swapups) {
            cout << (x + 1) << '\n';
        }
    }

    return 0;
}
