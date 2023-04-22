#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int find_ltr(const string &xs) {
    int ans = 0;

    int i = -1;
    while (i < sz(xs)) {
        const auto i0_ = xs.find('o', i + 1);
        if (i0_ == xs.npos) break;
        const auto i0 = inof(i0_);

        for (i = i0 + 1; i < sz(xs);) {
            if (xs[i] == '-') {
                ans = max(ans, i - i0);
                ++i;
                break;
            } else {
                ++i;
            }
        }
    }

    return ans ? ans : -1;
}

int find_greatest_x(string xs) {
    const auto o1 = find_ltr(xs);
    reverse(begin(xs), end(xs));
    const auto o2 = find_ltr(xs);
    return max(o1, o2);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    string xs;
    cin >> xs;
    assert(sz(xs) == N);

    cout << find_greatest_x(move(xs)) << '\n';
    return 0;
}
