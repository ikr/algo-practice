#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> positions(const string &haystack, const string &needle) {
    vector<int> ans;
    ans.reserve(haystack.size() / 4);

    for (auto it = haystack.find(needle); it != string::npos;
         it = haystack.find(needle, it + 1)) {
        ans.push_back(it);
    }

    return ans;
}

int solve(const string &s) {
    const auto xs = positions(s, "KICK");
    const auto ys = positions(s, "START");
    ll ans = 0;

    for (const auto x : xs) {
        ans += distance(lower_bound(cbegin(ys), cend(ys), x), cend(ys));
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        string s;
        cin >> s;
        cout << "Case #" << i << ": " << solve(s) << '\n';
    }

    return 0;
}
