#include <bits/stdc++.h>
using namespace std;

constexpr int N_MAX = 1e4;

vector<int> frequences(const vector<int> &xs) {
    vector<int> ans(N_MAX + 1, 0);
    for (const auto x : xs) ++ans[x];
    ans.erase(remove(begin(ans), end(ans), 0), cend(ans));
    return ans;
}

int find_mode(const vector<int> &xs) {
    unordered_map<int, int> cs;

    for (const auto x : xs) ++cs[x];

    int hi = 0;

    for (const auto [k, v] : cs) {
        hi = max(hi, v);
    }

    set<int> ans;
    for (const auto [k, v] : cs) {
        if (v == hi) ans.insert(k);
    }
    return *ans.cbegin();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n, 0);
        for (auto &x : xs) cin >> x;

        cout << find_mode(frequences(xs)) << '\n';
    }

    return 0;
}
