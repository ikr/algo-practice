#include <bits/stdc++.h>
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
    while (t--) {
        int n;
        cin >> n;

        int odds{}, odd_of_evens{}, even_of_evens{};
        for (int i = 0; i != n; ++i) {
            int x;
            cin >> x;

            if (x % 2) {
                ++odds;
            } else if ((x % 2) % 2) {
                ++odd_of_evens;
            } else {
                ++even_of_evens;
            }
        }

        const auto result = max({odds, odd_of_evens, even_of_evens});
        cout << result << '\n';
    }

    return 0;
}
