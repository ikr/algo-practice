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

constexpr bool are_seq(const char x, const char y) {
    return inof(x) + 1 == inof(y);
}

constexpr char max(const char x, const char y) {
    return inof(x) >= inof(y) ? x : y;
}

bool is_alphabetical(const string &s) {
    string::size_type l = s.find('a');
    if (l == string::npos) return false;

    string::size_type n = s.size();
    string::size_type r = l;
    while (l > 0 || r < n - 1) {
        if (l > 0) {
            if (are_seq(max(s[l], s[r]), s[l - 1])) {
                --l;
                continue;
            }
        }

        if (r < n - 1) {
            if (are_seq(max(s[l], s[r]), s[r + 1])) {
                ++r;
                continue;
            }
        }

        return false;
    }

    return true;
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

        cout << (is_alphabetical(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
