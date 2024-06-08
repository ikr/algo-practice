#include <bits/stdc++.h>
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

    const auto num_lower = inof(count_if(
        cbegin(xs), cend(xs), [](const char x) { return islower(x); }));
    const auto num_upper = sz(xs) - num_lower;

    if (num_upper > num_lower) {
        transform(cbegin(xs), cend(xs), begin(xs),
                  [](const char x) { return toupper(x); });
    } else {
        transform(cbegin(xs), cend(xs), begin(xs),
                  [](const char x) { return tolower(x); });
    }
    cout << xs << '\n';
    return 0;
}
