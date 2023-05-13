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

    string xs;
    cin >> xs;
    assert(sz(xs) == N);

    const auto t = count(cbegin(xs), cend(xs), 'T');
    const auto a = N - t;

    const auto ans = [&]() -> char {
        if (t > a) return 'T';
        if (a > t) return 'A';

        return xs.back() == 'T' ? 'A' : 'T';
    }();

    cout << ans << '\n';
    return 0;
}
