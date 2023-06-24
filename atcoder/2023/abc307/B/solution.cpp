#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<string> xs(N);
    for (auto &x : xs) cin >> x;

    bool yes = false;

    for (int i = 0; i < N - 1; ++i) {
        for (int j = i + 1; j < N; ++j) {
            {
                const auto y = xs[i] + xs[j];
                auto y_ = y;
                reverse(begin(y_), end(y_));
                if (y == y_) {
                    yes = true;
                    break;
                }
            }

            {
                const auto y = xs[j] + xs[i];
                auto y_ = y;
                reverse(begin(y_), end(y_));
                if (y == y_) {
                    yes = true;
                    break;
                }
            }
        }

        if (yes) break;
    }

    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
