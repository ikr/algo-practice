#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool same_parity(const vector<int> &xs) {
    if (xs.empty()) return true;
    return all_of(cbegin(xs), cend(xs),
                  [&](const int x) { return x % 2 == xs[0] % 2; });
}

bool is_possible(const vector<int> &xs) {
    vector<int> a;
    vector<int> b;

    for (int i = 0; i < sz(xs); ++i) {
        if (i % 2) {
            a.push_back(xs[i]);
        } else {
            b.push_back(xs[i]);
        }
    }

    return same_parity(a) && same_parity(b);
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
