#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int A, B, C, D;
    cin >> A >> B >> C >> D;

    const int t = A * 60 * 60 + B * 60;
    const int a = C * 60 * 60 + D * 60 + 1;

    cout << (a < t ? "Aoki" : "Takahashi") << '\n';
    return 0;
}
