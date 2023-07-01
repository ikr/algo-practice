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

    vector<string> C(N);
    for (auto &c : C) cin >> c;

    vector<string> D(M);
    for (auto &d : D) cin >> d;

    vector<int> P(M + 1);
    for (auto &p : P) cin >> p;

    map<string, int> m;
    for (int i = 0; i < M; ++i) {
        m[D[i]] = P[i + 1];
    }

    int ans{};

    for (const auto &c : C) {
        const auto it = m.find(c);
        if (it != cend(m)) {
            ans += it->second;
        } else {
            ans += P[0];
        }
    }

    cout << ans << '\n';
    return 0;
}
