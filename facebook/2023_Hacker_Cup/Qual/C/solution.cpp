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

static constexpr int INF = INT_MAX;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int opt_mid(const vector<int> &xs) {
    const auto target = xs[0] + xs.back();
    const auto n = sz(xs);
    const auto m = xs[n / 2];
    if (m >= target) return INF;

    for (int i = n / 2 - 1, j = n / 2 + 1; i >= 0 && j < n; --i, ++j) {
        if (xs[i] + xs[j] != target) return INF;
    }

    return target - m;
}

int opt_left(const vector<int> &xs) {
    const auto n = sz(xs);
    const auto target = xs[n / 2 - 1] + xs[n / 2];
    int result = INF;

    cerr << "(left) xs:" << xs << " target:" << target << endl;

    for (int i = n / 2 - 2, j = n / 2 + 1, replaced{}; i >= -1 && j < n; ++j) {
        cerr << "i:" << i << " j:" << j << " replaced:" << replaced << endl;
        if (i > 0 && xs[i] + xs[j] == target) {
            --i;
            cerr << "OK" << endl;
        } else {
            if (xs[j] >= target || replaced) {
                cerr << "INF" << endl;
                return INF;
            }
            result = target - xs[j];
            replaced = 1;
            cerr << "Adjusted" << endl;
        }
    }

    return result;
}

int opt_right(const vector<int> &xs) {
    const auto n = sz(xs);
    const auto target = xs[n / 2] + xs[n / 2 + 1];
    int result = INF;

    cerr << "(right) xs:" << xs << " target:" << target << endl;

    for (int i = n / 2 - 1, j = n / 2 + 2, replaced{}; i >= 0 && j <= n; --i) {
        cerr << "i:" << i << " j:" << j << " replaced:" << replaced << endl;
        if (j < n && xs[i] + xs[j] == target) {
            ++j;
            cerr << "OK" << endl;
        } else {
            if (xs[i] >= target || replaced) {
                cerr << "INF" << endl;
                return INF;
            }
            result = target - xs[i];
            replaced = 1;
            cerr << "Adjusted" << endl;
        }
    }

    return result;
}

int min_possible_apple_weight(const vector<int> &xs) {
    if (sz(xs) == 1) return 1;
    return min({opt_mid(xs), opt_left(xs), opt_right(xs)});
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<int> xs(2 * N - 1);
        for (auto &x : xs) cin >> x;
        ranges::sort(xs);

        const auto ans = min_possible_apple_weight(xs);
        cout << "Case #" << i << ": " << (ans == INF ? -1 : ans) << '\n';
    }

    return 0;
}
