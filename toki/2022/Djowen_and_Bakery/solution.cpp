#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, M;
    cin >> N >> M;

    vector<int> xs(N + 1, 0);

    for (int i = 1; i <= M; ++i) {
        int j;
        cin >> j;

        ++xs[j];
        xs[j] %= 4;
    }

    const auto ans =
        count_if(cbegin(xs), cend(xs), [](const int x) { return x > 1; });

    cout << ans << '\n';
    return 0;
}
