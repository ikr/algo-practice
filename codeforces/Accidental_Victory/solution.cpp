#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<int> range(const int n) {
    vector<int> ans(n);
    iota(begin(ans), end(ans), 0);
    return ans;
}

vector<int> possible_winner_positions(const vector<int> &xs) {
    const int n = xs.size();
    auto idx = range(n);
    sort(begin(idx), end(idx),
         [&xs](const int i, const int j) { return xs[i] > xs[j]; });

    vector<long long> suff(n, xs[idx.back()]);
    for (int i = n - 2; i >= 0; --i) {
        suff[i] = suff[i + 1] + xs[idx[i]];
    }

    vector<int> ans{idx[0] + 1};
    ans.reserve(n / 2);

    for (int th = xs[idx[0]], i = 1; i < n; ++i) {
        if (xs[idx[i]] == th) {
            ans.push_back(idx[i] + 1);
            continue;
        }

        const auto rest = suff[i];
        if (rest < th) break;

        ans.push_back(idx[i] + 1);
        th = xs[idx[i]];
    }

    sort(begin(ans), end(ans));
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        const auto ans = possible_winner_positions(xs);
        cout << ans.size() << '\n' << ans << '\n';
    }

    return 0;
}
