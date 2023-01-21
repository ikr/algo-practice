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

    string a;
    cin >> a;
    assert(sz(a) == N);

    string b{a[0]};
    for (int i = 1; i < sz(a); ++i) {
        if (a[i - 1] == 'n' && a[i] == 'a') {
            b += "ya";

        } else {
            b += a[i];
        }
    }

    cout << b << '\n';
    return 0;
}
