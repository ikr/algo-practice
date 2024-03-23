#include <bits/stdc++.h>
using namespace std;

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

    int n;
    cin >> n;
    vector<int> xs(n);
    for (auto &x : xs) cin >> x;

    vector<int> ys(n - 1, 0);
    for (int i = 0; i < n - 1; ++i) {
        ys[i] = xs[i] * xs[i + 1];
    }
    cout << ys << '\n';
    return 0;
}
