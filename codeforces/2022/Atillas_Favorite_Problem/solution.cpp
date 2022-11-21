#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_asize(const string &xs) {
    set<int> A;
    for (const auto x : xs) {
        A.insert(inof(x) - inof('a'));
    }
    return *crbegin(A) + 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs;
        cin >> xs;
        assert(sz(xs) == n);

        cout << min_asize(xs) << '\n';
    }

    return 0;
}
