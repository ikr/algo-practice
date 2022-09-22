#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const int A, const int B) {
    if ((A % 2) && (B % 2)) return false;
    if (A == 1 || B == 1) return false;
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int A, B;
        cin >> A >> B;

        cout << (is_possible(A, B) ? "Yes" : "No") << '\n';
    }

    return 0;
}
