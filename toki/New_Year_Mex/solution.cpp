#include <bits/stdc++.h>
using namespace std;

vector<int> reorder(vector<int> xs) {
    set<int> xss(cbegin(xs), cend(xs));
    if (!xss.count(1)) return xs;

    const bool has_2 = xss.count(2);
    xss.erase(1);
    if (has_2) xss.erase(2);

    vector<int> ans(xss.size() + 1, 1);
    copy(cbegin(xss), cend(xss), next(begin(ans)));
    if (has_2) ans.push_back(2);

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    const auto ans = reorder(xs);
    for (auto i = cbegin(ans); i != cend(ans); ++i) {
        if (i != cbegin(ans)) cout << ' ';
        cout << *i;
    }

    cout << '\n';
    return 0;
}
