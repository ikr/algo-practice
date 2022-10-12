#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll impl_a(const vector<int> &xs, const int k) {
    priority_queue<int, vector<int>, greater<int>> q;

    for (int i = 1; i < xs.back(); ++i) {
        if (!binary_search(cbegin(xs), cend(xs), i)) {
            q.push(i);
        }
    }

    ll result{};

    for (int i = 1; i <= k && !q.empty(); ++i) {
        const auto x = q.top();
        q.pop();

        result += xs.back() - x;
    }

    return result;
}

ll impl_b(vector<int> xs, int k) {
    const auto n = sz(xs);

    xs.push_back(2 * n);
    --k;

    priority_queue<int, vector<int>, greater<int>> q;

    for (int i = 1; i < xs.back(); ++i) {
        if (!binary_search(cbegin(xs), cend(xs), i)) {
            q.push(i);
        }
    }

    ll result{};

    for (int i = 1; i <= k && !q.empty(); ++i) {
        const auto x = q.top();
        q.pop();

        result += xs.back() - x;
    }

    return result;
}

ll max_scores_sum(vector<int> xs, int k) {
    const auto o1 = impl_a(xs, k);
    const auto o2 = impl_b(move(xs), k);
    return max(o1, o2);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));

        cout << max_scores_sum(move(xs), k) << '\n';
    }

    return 0;
}
