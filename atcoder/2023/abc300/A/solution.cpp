#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, A, B;
    cin >> N >> A >> B;

    vector<int> C(N);
    for (auto &c : C) cin >> c;

    const auto it =
        find_if(cbegin(C), cend(C), [&](const int c) { return c == A + B; });
    const auto ans = inof(distance(cbegin(C), it)) + 1;
    cout << ans << '\n';
    return 0;
}
