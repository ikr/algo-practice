#include <bits/stdc++.h>
using namespace std;

struct Shop final {
    int dist;
    int cost;
    int stock;
};

int min_cost(vector<Shop> ss) {
    sort(begin(ss), end(ss),
         [](const Shop &lhs, const Shop &rhs) { return lhs.dist < rhs.dist; });

    int ans = INT_MAX;

    for (const auto [d, c, s] : ss) {
        if (s - d > 0) {
            ans = min(ans, c);
        }
    }

    return ans == INT_MAX ? -1 : ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<Shop> ss(n);
    for (auto &[a, p, x] : ss) cin >> a >> p >> x;

    cout << min_cost(move(ss)) << '\n';
    return 0;
}
