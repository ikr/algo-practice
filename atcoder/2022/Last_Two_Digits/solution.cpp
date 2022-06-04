#include <iostream>
#include <string>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;

    const auto xs = to_string(t);
    const int n = sz(xs);
    cout << xs[n - 2] << xs[n - 1] << '\n';

    return 0;
}
