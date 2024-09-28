#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string kb;
    cin >> kb;

    vector<int> idx(26, -1);
    for (int i = 0; i < 26; ++i) {
        const auto x = inof(kb[i]) - inof('A');
        idx[x] = i;
    }

    int result{};
    int i = idx[0];
    for (int x = 0; x < 26; ++x) {
        result += abs(i - idx[x]);
        i = idx[x];
    }
    cout << result << '\n';
    return 0;
}
