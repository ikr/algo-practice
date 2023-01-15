#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int A, B;
    cin >> A >> B;

    int result = 1;

    for (int i = 1; i <= B; ++i) {
        result *= A;
    }

    cout << result << '\n';
    return 0;
}
