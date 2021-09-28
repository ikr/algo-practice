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

map<char, int> gather_freqs(const string &xs) {
    map<char, int> ans;
    for (const auto x : xs) ++ans[x];
    return ans;
}

bool can_go_to_empty(const string &xs) {
    auto fs = gather_freqs(xs);
    const int a = fs['A'];
    const int b = fs['B'];
    const int c = fs['C'];

    return b == a + c;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;

        cout << (can_go_to_empty(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
