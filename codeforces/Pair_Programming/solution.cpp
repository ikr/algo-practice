#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vi common_seq(int k, deque<int> a, deque<int> b) {
    vi ans;
    ans.reserve(sz(a) + sz(b));

    while (!a.empty() || !b.empty()) {
        if (!a.empty()) {
            if (a.front() == 0) {
                ++k;
                ans.push_back(a.front());
                a.pop_front();
                continue;
            }

            if (a.front() <= k) {
                ans.push_back(a.front());
                a.pop_front();
                continue;
            }
        }

        if (!b.empty()) {
            if (b.front() == 0) {
                ++k;
                ans.push_back(b.front());
                b.pop_front();
                continue;
            }

            if (b.front() <= k) {
                ans.push_back(b.front());
                b.pop_front();
                continue;
            }
        }

        return {};
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int k, n, m;
        cin >> k >> n >> m;

        deque<int> a(n);
        for (auto &x : a) cin >> x;

        deque<int> b(m);
        for (auto &x : b) cin >> x;

        const auto ans = common_seq(k, move(a), move(b));
        if (ans.empty()) {
            cout << "-1\n";
        } else {
            cout << ans << '\n';
        }
    }

    return 0;
}
