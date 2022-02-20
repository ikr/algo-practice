#include <iostream>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int a, b;
    cin >> a >> b;
    if (a > b) swap(a, b);

    const auto ans = [&]() -> bool {
        if (a == 1 && b == 10) return true;
        return b - a == 1;
    }();

    cout << (ans ? "Yes" : "No") << '\n';
    return 0;
}
