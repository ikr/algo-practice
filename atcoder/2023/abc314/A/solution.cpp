#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    const string src{"141592653589793238462643383279502884197169399375105820974"
                     "9445923078164062862089986280348253421170679"};

    cout << "3.";
    cout << src.substr(0, N) << '\n';

    return 0;
}
