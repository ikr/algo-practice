#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll max_intersections(const vector<int> &xs) {
    ll result{};

    for (int i = sz(xs) - 1; i >= 0; --i) {
        const auto x = xs[i];

        for (int j = 0; j < i; ++j) {
            if (xs[j] >= x) ++result;
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
        for (auto &x : xs) {
            cin >> x;
            --x;
        }

        cout << max_intersections(xs) << '\n';
    }

    return 0;
}
