#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<int> do_fill(const int n, const int x, const int y, const int step) {
    vector<int> ans;
    ans.reserve(n);

    for (int i = x; i <= y; i += step) ans.push_back(i);

    while (ans.size() < n && ans.front() - step > 0) {
        ans.insert(cbegin(ans), ans.front() - step);
    }

    while (ans.size() < n) {
        ans.push_back(ans.back() + step);
    }

    return ans;
}

vector<int> opt_seq(const int n, const int x, const int y) {
    assert(x <= y);
    const int d = y - x;

    for (int i = 1; i <= d; ++i) {
        if (d % i) continue;

        const int can_fit = d / i + 1;
        if (can_fit <= n) return do_fill(n, x, y, i);
    }

    assert(false && "failed assumptions");
    return {};
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, x, y;
        cin >> n >> x >> y;
        cout << opt_seq(n, min(x, y), max(x, y)) << '\n';
    }

    return 0;
}
