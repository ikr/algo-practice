#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string solution(string xs) {
    if (sz(xs) < 3) return xs;
    sort(begin(xs), end(xs));
    return xs;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N;
        cin >> N;

        string xs;
        cin >> xs;
        assert(sz(xs) == N);

        cout << solution(move(xs)) << '\n';
    }

    return 0;
}
