#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int replacements_to_palindrome(const string &xs) {
    int ans{};
    for (int i = 0; i < sz(xs) / 2; ++i) {
        ans += xs[i] != xs[sz(xs) - 1 - i];
    }
    return ans;
}

ll min_yen(const string &S, const ll A, const ll B) {
    ll ans = LONG_LONG_MAX;
    for (int rotations = 0; rotations < sz(S) - 1; ++rotations) {
        auto xs = S;
        rotate(begin(xs), begin(xs) + rotations, end(xs));
        const auto replacements = replacements_to_palindrome(xs);

        ans = min(ans, A * rotations + B * replacements);
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    ll A, B;
    cin >> A >> B;

    string xs;
    cin >> xs;
    assert(sz(xs) == N);

    cout << min_yen(xs, A, B) << '\n';
    return 0;
}
