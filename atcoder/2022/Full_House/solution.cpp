#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    map<int, int> xs;

    for (int i = 1; i <= 5; ++i) {
        int x;
        cin >> x;
        ++xs[x];
    }

    const auto yes = [&]() -> bool {
        if (sz(xs) != 2) return false;
        return (cbegin(xs)->second == 2 && crbegin(xs)->second == 3) ||
               (cbegin(xs)->second == 3 && crbegin(xs)->second == 2);
    }();

    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
