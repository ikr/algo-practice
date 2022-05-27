#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int A, B, C;
    cin >> A >> B >> C;

    const auto yes = A == B && B == C;
    cout << (yes ? "Yes" : "No") << '\n';

    return 0;
}
