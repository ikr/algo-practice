#include <bits/stdc++.h>
using namespace std;

map<int, int> gather_counts(const vector<int> &xs) {
    map<int, int> ans;
    for (const int x : xs) ++ans[x];
    return ans;
}

int last_x(const vector<int> &xs) {
    auto cs = gather_counts(xs);
    while (cs.size() != 1) {
        const int lo = cbegin(cs)->first;
        const int hi = crbegin(cs)->first;
        const int x = crbegin(cs)->second;

        cs.erase(hi);
        cs[hi - lo] += x;
    }
    return cs.begin()->first;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n, 0);
    for (auto &x : xs) cin >> x;

    cout << last_x(xs) << '\n';
    return 0;
}
