#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_groups(const vector<int> &xs, const vector<int> &ys) {
    multiset<int> slackers;
    priority_queue<int> sponsors;
    int neutrals{};

    for (int i = 0; i < sz(xs); ++i) {
        const auto sur = ys[i] - xs[i];

        if (sur < 0) {
            slackers.insert(-sur);
        } else if (sur > 0) {
            sponsors.push(sur);
        } else {
            assert(sur == 0);
            ++neutrals;
        }
    }

    int result = neutrals / 2;
    neutrals %= 2;

    while (!sponsors.empty()) {
        const auto sur = sponsors.top();
        sponsors.pop();

        auto it = slackers.lower_bound(sur);
        if (it != cend(slackers) && *it == sur) {
            slackers.erase(it);
            ++result;
        } else if (slackers.empty() || it == cbegin(slackers)) {
            if (neutrals > 0) {
                neutrals = 0;
                ++result;
            } else if (!sponsors.empty()) {
                sponsors.pop();
                ++result;
            }
        } else {
            it = prev(it);
            slackers.erase(it);
            ++result;
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        vector<int> ys(n);
        for (auto &y : ys) cin >> y;

        cout << max_groups(xs, ys) << '\n';
    }

    return 0;
}
