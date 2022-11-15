#include <bits/stdc++.h>
using namespace std;

int max_score(vector<int> xs, const vector<int> &ys) {
    sort(begin(xs), end(xs));
    multiset<int> opp(cbegin(ys), cend(ys));
    int result{};

    {
        vector<int> xs_;
        while (!xs.empty()) {
            const auto x = xs.back();
            xs.pop_back();

            const auto it = opp.lower_bound(x);
            if (it != cbegin(opp)) {
                opp.erase(prev(it));
                ++result;
            } else {
                xs_.push_back(x);
            }
        }
        swap(xs_, xs);
    }

    for (const auto x : xs) {
        const auto it = opp.find(x);
        if (it != cend(opp)) {
            opp.erase(it);
        } else {
            --result;
        }
    }

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

    cout << max_score(move(xs), ys) << '\n';
    return 0;
}
