#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int A_MAX = 1000;

int solution(const vector<int> &xs) {
    vector<int> max_position(A_MAX + 1, -1);
    for (int i = 1; i < sz(xs); ++i) {
        max_position[xs[i]] = i + 1;
    }

    int result = -1;

    for (int i = 1; i < sz(max_position); ++i) {
        for (int j = i; j < sz(max_position); ++j) {
            if (max_position[i] == -1 || max_position[j] == -1) {
                continue;
            }

            if (__gcd(i, j) == 1) {
                result = max(result, max_position[i] + max_position[j]);
            }
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

        vector<int> xs(n);
        for (auto &x : xs) cin >> x;

        cout << solution(xs) << '\n';
    }

    return 0;
}
