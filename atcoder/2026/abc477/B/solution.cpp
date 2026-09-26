#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_apart(const vector<int> &xs, const int d, const int i0) {
    for (int i = 0; i != sz(xs); ++i) {
        if (i == i0) continue;
        if (abs(xs[i0] - xs[i]) < d) return false;
    }

    return true;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, d;
    cin >> n >> d;

    vector<int> xs(n);
    for (auto &x : xs) {
        cin >> x;
    }

    vector<int> result;
    for (int i = 0; i != sz(xs); ++i) {
        if (is_apart(xs, d, i)) {
            result.push_back(i + 1);
        }
    }

    cout << sz(result) << '\n';
    if (!result.empty()) {
        cout << result << '\n';
    }

    return 0;
}
