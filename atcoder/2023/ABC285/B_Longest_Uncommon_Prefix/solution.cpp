#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int AZ = 26;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    string xs;
    cin >> xs;
    assert(sz(xs) == N);

    vector<int> ans(N - 1, 0);

    for (int j = 1; j <= N - 1; ++j) {
        int a = 0;
        int b = j;

        while (a < N && b < N) {
            if (xs[a] == xs[b]) {
                break;

            } else {
                ++ans[j - 1];
            }

            ++a;
            ++b;
        }
    }

    for (const auto &a : ans) {
        cout << a << '\n';
    }
    return 0;
}
