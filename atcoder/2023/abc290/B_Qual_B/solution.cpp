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

    string xs;
    cin >> xs;
    assert(sz(xs) == N);

    auto ans = xs;
    int adv{};
    for (int i = 0; i < N; ++i) {
        if (adv == K) {
            ans[i] = 'x';
            continue;
        }

        adv += (xs[i] == 'o');
    }

    cout << ans << '\n';
    return 0;
}
