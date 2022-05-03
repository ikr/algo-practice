#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<int> &zs) {
    auto ys = zs;

    for (int i = sz(ys) - 1; i > 0; i -= 2) {
        if (ys[i] < ys[i - 1]) {
            swap(ys[i], ys[i - 1]);
        }
    }
    return is_sorted(cbegin(ys), cend(ys));
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

        cout << (is_possible(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
