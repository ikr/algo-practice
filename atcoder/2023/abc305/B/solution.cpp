#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    char P, Q;
    cin >> P >> Q;

    if (Q < P) swap(P, Q);
    const auto p = inof(P) - inof('A');
    const auto q = inof(Q) - inof('A');

    const array xs{0, 3, 1, 4, 1, 5, 9};
    vector<int> ss(sz(xs));
    partial_sum(cbegin(xs), cend(xs), begin(ss));

    const auto ans = ss[q] - ss[p];
    cout << ans << '\n';
    return 0;
}
