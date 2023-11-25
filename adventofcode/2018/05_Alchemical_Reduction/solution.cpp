#include <bits/stdc++.h>
using namespace std;

static constexpr int Az = 26;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr bool react(const char x, const char y) {
    return x != y && tolower(x) == tolower(y);
}

string chain_react(const string &xs) {
    string ys;
    for (const auto x : xs) {
        if (!ys.empty() && react(ys.back(), x)) {
            ys.pop_back();
        } else {
            ys.push_back(x);
        }
    }
    return ys;
}

string omit_Aa(const string &xs, const char A) {
    string ys;
    for (const auto x : xs) {
        if (x != A && x != tolower(A)) ys.push_back(x);
    }
    return ys;
}

int main() {
    string xs;
    cin >> xs;

    int lo = INT_MAX;
    for (char A = 'A'; A < 'A' + Az; ++A) {
        const auto ys = omit_Aa(xs, A);
        const auto zs = chain_react(ys);
        lo = min(lo, sz(zs));
    }

    cout << lo << '\n';
    return 0;
}
