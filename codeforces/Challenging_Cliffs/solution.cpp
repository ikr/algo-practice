#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

int min_diff_index(const vi &xs) {
    int ans = -1;
    int best = INT_MAX;

    for (int i = 0; i < sz(xs) - 1; ++i) {
        const int curr = xs[i + 1] - xs[i];

        if (curr < best) {
            best = curr;
            ans = i;
        }
    }

    return ans;
}

vi optimal_course(vi xs) {
    sort(begin(xs), end(xs));
    if (sz(xs) == 2) return xs;

    const auto p = min_diff_index(xs);
    rotate(begin(xs), begin(xs) + p + 1, end(xs));
    return xs;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vi xs(n);
        for (auto &x : xs) cin >> x;
        cout << optimal_course(xs) << '\n';
    }

    return 0;
}
