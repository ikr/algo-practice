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
        int n, k;
        cin >> n >> k;

        string xs;
        cin >> xs;

        vector<bool> free_by_farm(n / k, false);

        for (int i = 0; i != sz(xs); ++i) {
            const int j = i / k;
            if (xs[i] == '0') free_by_farm[j] = true;
        }

        const auto result =
            count(cbegin(free_by_farm), cend(free_by_farm), false);
        cout << result << '\n';
    }

    return 0;
}
