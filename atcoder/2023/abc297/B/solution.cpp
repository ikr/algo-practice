#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    const int ik = xs.find('K');

    vector<int> ib;
    vector<int> ir;

    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == 'B') {
            ib.push_back(i);
        } else if (xs[i] == 'R') {
            ir.push_back(i);
        }
    }

    assert(sz(ib) == 2);
    assert(sz(ir) == 2);

    const auto yes = (ib[0] % 2 != ib[1] % 2) && (ir[0] < ik && ik < ir[1]);
    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
