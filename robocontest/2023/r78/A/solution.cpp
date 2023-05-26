#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> vector<int> digits_reversed(T n) {
    vector<int> ans;

    while (n) {
        ans.push_back(inof(n % static_cast<T>(10)));
        n /= static_cast<T>(10);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    const auto ds = digits_reversed(stoll(xs));
    const auto yes = (sz(xs) % 2) && all_of(cbegin(ds), cend(ds),
                                            [](const int d) { return d % 2; });

    cout << (yes ? "YES" : "NO") << '\n';
    return 0;
}
