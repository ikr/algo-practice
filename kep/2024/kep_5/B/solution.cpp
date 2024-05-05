#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

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

    auto ys = xs;
    reverse(begin(ys), end(ys));

    const auto a = stoll(xs) + stoll(ys);
    const auto ds = digits_reversed(a);
    const auto yes =
        all_of(cbegin(ds), cend(ds), [](const int d) { return d % 2; });

    cout << (yes ? "Yes" : "No") << '\n';
    return 0;
}
