#include <bits/stdc++.h>
using namespace std;

set<int> make_scratch(const int n) {
    set<int> ans;
    for (int i = 0; i <= n; ++i) ans.insert(i);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n, 0);
    for (auto &x : xs) cin >> x;

    const auto hi = *max_element(cbegin(xs), cend(xs));
    auto scratch = make_scratch(hi);
    for (const int x : xs) {
        scratch.erase(x);
        const int ans = scratch.empty() ? hi + 1 : *scratch.begin();
        cout << ans << '\n';
    }

    return 0;
}
