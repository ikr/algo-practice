#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    int facts_count;
    cin >> n >> facts_count;

    vector diffs(n, -1);
    vector<pair<int, int>> unsorted_ranges;

    for (int i = 0; i != facts_count; ++i) {
        int t;
        int l;
        int r;
        cin >> t >> l >> r;

        assert(t == 0 || t == 1);

        if (t)
            fill(diffs.begin() + l, diffs.begin() + r, 0);
        else
            unsorted_ranges.push_back({l, r});
    }

    vector ans(n + 1, n);
    for (auto i = 2; i <= n; ++i) {
        ans[i] = ans[i - 1] + diffs[i - 1];
    }

    for (auto [l, r] : unsorted_ranges) {
        if (is_sorted(ans.cbegin() + l, ans.cbegin() + r + 1)) {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n" << ans[1];
    for_each(ans.cbegin() + 2, ans.cend(),
             [](const auto x) { cout << ' ' << x; });
    cout << '\n';

    return 0;
}
