#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using ll = long long;

ll population_size(const string &s, const string &t) {
    if (t == "a") return 1;
    if (count(cbegin(t), cend(t), 'a') > 0) return -1;
    return (1LL << sz(s));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;

        string t;
        cin >> t;

        cout << population_size(s, t) << '\n';
    }

    return 0;
}
