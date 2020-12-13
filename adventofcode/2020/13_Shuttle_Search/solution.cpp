#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<string> tokenize(const regex &delim, const string &s) {
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), delim, -1),
                          sregex_token_iterator{});
}

vector<pair<ll, int>> gather_ids_with_deltas(const vector<string> &tt) {
    const int n = tt.size();
    vector<pair<ll, int>> ans{{stoll(tt.front()), 0}};

    for (int i = 1; i < n; ++i) {
        if (tt[i] == "x") continue;
        ans.emplace_back(stoll(tt[i]), i);
    }

    return ans;
}

bool is_target(const vector<pair<ll, int>> &ids_ds, const ll x) {
    for (const auto [id, d] : ids_ds) {
        if ((x + d) % id != 0LL) return false;
    }

    return true;
}

ll solve(const vector<string> &tt) {
    const auto ids_ds = gather_ids_with_deltas(tt);
    ll x = ids_ds.front().first;
    while (!is_target(ids_ds, x)) x += 7LL;
    return x;
}

int main() {
    int t;
    cin >> t;
    string s;
    cin >> s;

    cout << solve(tokenize(regex(","), s)) << '\n';
    return 0;
}
