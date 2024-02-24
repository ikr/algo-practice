#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    int Q;
    cin >> Q;

    for (int i = 1; i <= Q; ++i) {
        int a, b;
        cin >> a >> b;

        const auto ia = find(cbegin(xs), cend(xs), a);
        const auto ib = find(cbegin(xs), cend(xs), b);

        if (ia < ib) {
            cout << a << '\n';
        } else {
            cout << b << '\n';
        }
    }

    return 0;
}
