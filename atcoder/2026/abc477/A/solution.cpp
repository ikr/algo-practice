#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const string colors{"BYR"};

    char x;
    cin >> x;

    const int i0 = inof(distance(cbegin(colors), ranges::find(colors, x)));
    const int i1 = (i0 + 1) % 3;

    cout << colors[i1] << '\n';
    return 0;
}
