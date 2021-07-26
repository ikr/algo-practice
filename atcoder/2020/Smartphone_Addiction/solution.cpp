#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m, t;
    cin >> n >> m >> t;

    vector<pair<int, int>> rests;
    while (m--) {
        int a, b;
        cin >> a >> b;
        rests.emplace_back(a, b);
    }

    int capacity = n;
    int current_time = 0;
    for (const auto [a, b] : rests) {
        if (capacity <= a - current_time) {
            capacity = 0;
            break;
        }

        capacity -= (a - current_time);
        capacity = min(n, capacity + (b - a));
        current_time = b;
    }

    cout << ((capacity > (t - current_time)) ? "Yes" : "No") << '\n';
    return 0;
}
