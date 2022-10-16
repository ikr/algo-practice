#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int max_wait_time(const string &xs, const char initial_color) {
    if (initial_color == 'g') return 0;
    const auto n = sz(xs);

    vector<int> initial_color_indices;
    vector<int> green_color_idices;

    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == 'g') {
            green_color_idices.push_back(i);
        } else if (xs[i] == initial_color) {
            initial_color_indices.push_back(i);
        }
    }

    int result = -1;

    for (const auto j : initial_color_indices) {
        const auto it = lower_bound(cbegin(green_color_idices),
                                    cend(green_color_idices), j);

        if (it == cend(green_color_idices)) {
            result = max(result, n - 1 - j + green_color_idices[0] + 1);
        } else {
            result = max(result, *it - j);
        }
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        char c;
        cin >> c;

        string xs;
        cin >> xs;
        assert(sz(xs) == n);

        cout << max_wait_time(xs, c) << '\n';
    }

    return 0;
}
