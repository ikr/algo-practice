#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, K;
    cin >> N >> K;

    vector<int> A(N);
    for (auto &a : A) cin >> a;

    set<int> xss(cbegin(A), cend(A));
    vector<int> xs(cbegin(xss), cend(xss));

    const auto ans = [&]() -> int {
        if (xs[0]) return 0;

        for (int i = 1; i < K; ++i) {
            if (xs[i - 1] + 1 != xs[i]) return xs[i - 1] + 1;
        }

        return xs[K - 1] + 1;
    }();

    cout << ans << '\n';
    return 0;
}
