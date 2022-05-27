#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_ops(const int A, const int B) {
    if (A == B) return 0;
    if (A % B == 0 || B % A == 0 || abs(A - B) == 1) return 1;
    return 2;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int A, B;
    cin >> A >> B;
    cout << min_ops(A, B) << '\n';
    return 0;
}
