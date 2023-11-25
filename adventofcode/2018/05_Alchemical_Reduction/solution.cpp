#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr bool react(const char x, const char y) {
    return x != y && tolower(x) == tolower(y);
}

int main() {
    string xs;
    cin >> xs;

    string ys;
    for (const auto x : xs) {
        if (!ys.empty() && react(ys.back(), x)) {
            ys.pop_back();
        } else {
            ys.push_back(x);
        }
    }

    cout << ys << '\n' << sz(ys) << '\n';
    return 0;
}
