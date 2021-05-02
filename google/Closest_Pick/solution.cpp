#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

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

vi min_distances(const int k, const vi &xs) {
    vi ans(k + 1, INT_MAX);

    for (int w = 1; w <= k; ++w) {
        for (const auto x : xs) {
            ans[w] = min(ans[w], abs(x - w));
        }
    }

    return ans;
}

double solve(const int k, const vi &xs) {
    set<int> xss(cbegin(xs), cend(xs));

    vi ys;
    for (int i = 1; i <= k; ++i) {
        if (xss.count(i)) continue;
        ys.push_back(i);
    }

    if (ys.empty()) return 0;

    const auto md = min_distances(k, xs);

    double ans = 0;

    for (int i = 0; i < sz(ys); ++i) {
        for (int j = 0; j < sz(ys); ++j) {
            double curr = 0;

            for (int w = 1; w <= k; ++w) {
                if (abs(w - ys[i]) < md[w] || abs(w - ys[j]) < md[w]) {
                    curr += 1.0 / doof(k);
                }
            }

            ans = max(ans, curr);
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(7) << fixed;

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int n, k;
        cin >> n >> k;

        vi xs(n);
        for (auto &x : xs) cin >> x;

        sort(begin(xs), end(xs));
        xs.erase(unique(begin(xs), end(xs)), end(xs));

        cout << "Case #" << i << ": " << solve(k, xs) << '\n';
    }

    return 0;
}
