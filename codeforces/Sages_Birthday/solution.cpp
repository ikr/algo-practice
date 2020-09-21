#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<int> interleave(const vector<int> &xs, const int cheaps) {
    const int n = xs.size();
    vector<int> ans{xs[0]};
    ans.reserve(cheaps * 2 + 1);

    for (int l = 1, r = n - 1; l <= cheaps; ++l, --r) {
        ans.push_back(xs[r]);
        ans.push_back(xs[l]);
    }

    return ans;
}

pair<int, vector<int>> solve(vector<int> &xs) {
    const int n = xs.size();
    if (n <= 2) return {0, xs};

    sort(rbegin(xs), rend(xs));

    const int cnt = n % 2 == 0 ? (n / 2 - 1) : n / 2;
    return {cnt, interleave(xs, cnt)};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> xs(n, 0);
    for (auto &x : xs) cin >> x;
    const auto [cnt, ys] = solve(xs);

    cout << cnt << '\n';
    cout << ys << '\n';

    return 0;
}
