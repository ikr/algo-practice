#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_even_digit(const char x) {
    const set<char> xs{'2', '4', '6', '8'};
    return xs.count(x);
}

int min_ops(const string &xs) {
    if (is_even_digit(xs.back())) return 0;
    if (is_even_digit(xs[0])) return 1;

    return any_of(cbegin(xs), cend(xs), is_even_digit) ? 2 : -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        string n;
        cin >> n;

        cout << min_ops(n) << '\n';
    }

    return 0;
}
