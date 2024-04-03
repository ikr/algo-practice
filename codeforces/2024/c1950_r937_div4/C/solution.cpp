#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string pad(const int x) {
    const auto s = to_string(x);
    return sz(s) == 1 ? ("0" + s) : s;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string src;
        cin >> src;

        const auto hh = stoi(src.substr(0, 2));
        const auto mm = stoi(src.substr(3, 2));

        if (hh == 12) {
            cout << 12 << ":" << pad(mm) << " PM\n";
        } else if (hh == 0) {
            cout << 12 << ":" << pad(mm) << " AM\n";
        } else if (hh < 12) {
            cout << pad(hh) << ":" << pad(mm) << " AM\n";
        } else {
            cout << pad(hh - 12) << ":" << pad(mm) << " PM\n";
        }
    }

    return 0;
}
