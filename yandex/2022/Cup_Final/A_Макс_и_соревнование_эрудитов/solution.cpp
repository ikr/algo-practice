#include <bits/stdc++.h>
using namespace std;

int max_score(const vector<int> &xs, vector<int> ys) {
    multiset<int> xss(cbegin(xs), cend(xs));
    sort(begin(ys), end(ys));
    int result{};

    for (const auto y : ys) {
        const auto it = xss.upper_bound(y);

        if (it != cend(xss)) {
            ++result;
            xss.erase(it);
            continue;
        }

        const auto jt = xss.find(y);
        if (jt != cend(xss)) {
            xss.erase(jt);
            continue;
        }

        xss.erase(cbegin(xss));
        --result;
    }

    assert(xss.empty());
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    vector<int> ys(n);
    for (auto &y : ys) cin >> y;

    cout << max_score(xs, move(ys)) << '\n';
    return 0;
}
