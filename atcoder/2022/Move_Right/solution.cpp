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

    string xs;
    cin >> xs;

    for (int i = 3; i >= 0; --i) {
        xs[i + 1] = xs[i];
    }

    xs[0] = '0';
    cout << xs << '\n';

    return 0;
}
