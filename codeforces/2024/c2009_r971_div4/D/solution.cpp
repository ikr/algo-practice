#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

ll num_right(const vector<int> &up, const vector<int> &dn) {
    ll result{};

    for (const auto xu : up) {
        const auto [it, jt] = equal_range(cbegin(dn), cend(dn), xu);
        if (it != jt) {
            const auto i = inof(it - cbegin(dn));
            result += i;
            result += sz(dn) - 1 - i;
        }

        if (binary_search(cbegin(dn), cend(dn), xu - 1) &&
            binary_search(cbegin(dn), cend(dn), xu + 1)) {
            ++result;
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

        vector<int> up;
        vector<int> dn;

        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;

            if (y == 0) {
                dn.push_back(x);
            } else {
                assert(y == 1);
                up.push_back(x);
            }
        }

        sort(begin(up), end(up));
        sort(begin(dn), end(dn));

        cout << num_right(up, dn) + num_right(dn, up) << '\n';
    }

    return 0;
}
