#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

// https://cp-algorithms.com/string/z-function.html
vector<int> z_with_a_twist(const string &s) {
    const auto n = sz(s);
    vector<int> z(n);
    int l{};
    int r{};
    optional<int> ine;
    for (int i = 1; i < n; i++) {
        if (i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < n) {
            if (s[z[i]] == s[i + z[i]]) {
                z[i]++;
            } else if (!ine) {
                ine = i + z[i];
                z[i]++;
            } else {
                break;
            }
        }
        if (i + z[i] > r) {
            l = i;
            if (ine && *ine < l) ine.reset();
            r = i + z[i];
            if (ine && r <= *ine) ine.reset();
        }
    }
    cerr << z << endl;
    return z;
}

unordered_map<char, int> frequencies(const string &xs) {
    unordered_map<char, int> result;
    for (const char x : xs) ++result[x];
    return result;
}

bool confirm_m_pattern(const vector<int> &zs, const int m) {
    for (int i = m; i < sz(zs); i += m) {
        if (zs[i] < m) return false;
    }
    return true;
}

int solve(const string &xs, const vector<int> &zs) {
    const auto n = sz(xs);
    if (n < 3) return 1;

    {
        const auto fq = frequencies(xs);
        if (sz(fq) == 1 ||
            (sz(fq) == 2 && any_of(cbegin(fq), cend(fq), [](const auto kv) {
                 return kv.second == 1;
             }))) {
            return 1;
        }
    }

    for (int m = 2; llof(m) * m <= llof(n); ++m) {
        if (n % m) continue;
        if (confirm_m_pattern(zs, m)) return m;
    }
    return n;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs;
        cin >> xs;

        const auto o1 = solve(xs, z_with_a_twist(xs));

        reverse(begin(xs), end(xs));
        const auto o2 = solve(xs, z_with_a_twist(xs));
        cout << min(o1, o2) << '\n';
    }

    return 0;
}
