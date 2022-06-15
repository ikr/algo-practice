#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
using namespace std;

constexpr char chof(const int x) { return static_cast<char>(x); }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string gen_palin(const int N, const int X) {
    string pre;
    for (int i = 0; i < X - 1; ++i) {
        pre += chof(inof('a') + i);
    }

    const auto inf = chof(inof('a') + X - 1);

    string suf = pre;
    reverse(begin(suf), end(suf));

    if (N < sz(pre) + 1 + sz(suf)) return "-1";

    const auto to_fill = N - sz(pre) - sz(suf);
    return pre + string(to_fill, inf) + suf;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N, X;
        cin >> N >> X;

        cout << gen_palin(N, X) << '\n';
    }

    return 0;
}
