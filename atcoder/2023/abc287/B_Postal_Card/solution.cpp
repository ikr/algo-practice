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

    vector<int> S(N);
    for (int i = 0; i < N; ++i) {
        cin >> S[i];
    }

    set<int> T;
    for (int i = 0; i < M; ++i) {
        int a;
        cin >> a;
        T.insert(a);
    }

    int ans{};
    for (const auto x : S) {
        ans += inof(T.count(x % 1000));
    }

    cout << ans << '\n';
    return 0;
}
