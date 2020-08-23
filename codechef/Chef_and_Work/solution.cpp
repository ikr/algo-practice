#include <bits/stdc++.h>
using namespace std;

constexpr int W_MAX = 1000;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

vector<int> gather_counts(const vector<int> &xs) {
    vector<int> ans(W_MAX + 1, 0);
    for (const auto x : xs) ++ans[x];
    return ans;
}

int trips(const vector<int> &xs, const int k) {
    if (*max_element(cbegin(xs), cend(xs)) > k) return -1;

    auto cs = gather_counts(xs);
    int ans = 0;

    for (int i = W_MAX; i >= 1; --i) {
        if (cs[i] == 0) continue;
        const int q = i / k;
        const int r = i % k;
        cout << "q:" << q << " r:" << r << endl;

        ans += q * cs[i];

        if (r == 0) {
            cs[i] = 0;
            continue;
        }

        if (r < i) {
            cs[r] += cs[i];
            cs[i] = 0;
            continue;
        }

        assert(k > i);

        while (cs[i] != 0) {
            int j = k - i;
            while (j >= 1 && cs[j] == 0) --j;

            cout << "i:" << i << " j:" << j << endl;

            if (cs[j] == 0) {
                ans += cs[i];
                cs[i] = 0;
            } else {
                const int t = min(cs[i], cs[j]);
                cs[i] -= t;
                cs[j] -= t;
                ans += t;
            }
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> xs(n, 0);
        for (auto &x : xs) cin >> x;
        cout << trips(xs, k) << '\n';
    }

    return 0;
}
