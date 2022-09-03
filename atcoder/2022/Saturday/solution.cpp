#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const vector<string> xs{"Monday", "Tuesday", "Wednesday", "Thursday",
                            "Friday"};

    string s;
    cin >> s;

    const auto it = find(cbegin(xs), cend(xs), s);
    const auto i = 5 - inof(distance(cbegin(xs), it));

    cout << i << '\n';
    return 0;
}
