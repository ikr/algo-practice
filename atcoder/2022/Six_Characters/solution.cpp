#include <iostream>
#include <string>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s;
    cin >> s;

    string t;
    for (int i = 0; i < 6; ++i) {
        t += s;
    }

    cout << t.substr(0, 6) << '\n';

    return 0;
}
