#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int min_days(const string &xs) {
    int result{};
    set<char> mem;

    for (const auto x : xs) {
        if (sz(mem) == 3 && !mem.count(x)) {
            ++result;
            mem.clear();
            mem.insert(x);
        } else {
            mem.insert(x);
        }
    }

    if (!mem.empty()) ++result;

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        cout << min_days(xs) << '\n';
    }

    return 0;
}
