#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

vector<pii> all_moves(const int n) {
    vector<pii> ans;
    ans.reserve((1 << n) - 1);

    function<void(int, int, int, int)> recur;
    recur = [&](const int m, const int src, const int dest, const int aux) {
        if (!m) return;
        recur(m - 1, src, aux, dest);

        ans.emplace_back(src, dest);
        recur(m - 1, aux, dest, src);
    };

    recur(n, 0, 2, 1);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    const auto ans = all_moves(n);
    cout << ans.size() << '\n';
    for (const auto [a, b] : ans) {
        cout << (a + 1) << ' ' << (b + 1) << '\n';
    }
    return 0;
}
