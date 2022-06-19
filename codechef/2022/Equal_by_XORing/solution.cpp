#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_ops(const int A, const int B, const int N) {
    if (A == B) return 0;
    if ((A ^ B) < N) return 1;
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int A, B, N;
        cin >> A >> B >> N;
        cout << min_ops(A, B, N) << '\n';
    }

    return 0;
}
