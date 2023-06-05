#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    vector<int> P(n);
    for (auto &p : P) cin >> p;

    if (n <= 3) {
        cout << "1\nNO\n";
        return 0;
    }

    vector<int> io(n);
    iota(begin(io), end(io), 1);

    auto io_ = io;
    reverse(begin(io), end(io));

    if (P == io || P == io_) {
        cout << (n / 2) << "\nYES\n";
    } else {
        cout << ((n / 2) - 1) << "\nNO\n";
    }

    return 0;
}
