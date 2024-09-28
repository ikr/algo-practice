#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    vector<string> xss(12);
    for (auto &xs : xss) cin >> xs;

    int result{};
    for (int i = 0; i < 12; ++i) {
        result += sz(xss[i]) == i + 1;
    }
    cout << result << '\n';
    return 0;
}
