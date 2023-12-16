#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static const vector<ll> Base{1,
                             11,
                             111,
                             1111,
                             11111,
                             111111,
                             1111111,
                             11111111,
                             111111111LL,
                             1111111111LL,
                             1111111111LL,
                             11111111111LL,
                             111111111111LL,
                             1111111111111LL};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    set<ll> xs;
    for (const auto a : Base) {
        for (const auto b : Base) {
            for (const auto c : Base) {
                xs.insert(a + b + c);
            }
        }
    }

    const vector<ll> ys(cbegin(xs), cend(xs));

    int N;
    cin >> N;
    cout << ys[N - 1] << '\n';
    return 0;
}
