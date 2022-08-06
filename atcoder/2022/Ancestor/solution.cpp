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

    vector<int> ps(N, -1);
    for (int i = 1; i < N; ++i) {
        cin >> ps[i];
        --ps[i];
    }

    int result{};
    int x = N - 1;
    while (ps[x] >= 0) {
        ++result;
        x = ps[x];
    }

    cout << result << '\n';
    return 0;
}
