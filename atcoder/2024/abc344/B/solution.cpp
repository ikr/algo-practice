#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    vector<int> xs;

    for (string line; getline(cin, line);) {
        const auto x = stoi(line);
        xs.push_back(x);
        if (!x) break;
    }

    reverse(begin(xs), end(xs));
    for (const auto x : xs) cout << x << '\n';
    return 0;
}
