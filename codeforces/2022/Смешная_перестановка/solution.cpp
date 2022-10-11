#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> funny_perm(const int n) {
    if (n == 3) return {-1};
    if (n == 5) return {5, 4, 1, 2, 3};

    vector<int> result(n);
    iota(begin(result), end(result), 1);
    reverse(begin(result), end(result));

    if (n > 2 && (n % 2)) {
        swap(result[(n - 1) / 2 - 1], result[(n - 1) / 2]);
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

        cout << funny_perm(n) << '\n';
    }

    return 0;
}
