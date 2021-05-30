#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

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

vector<pii> encode(const string &xs) {
    vector<pii> ans;

    int val = -1;

    for (const auto x : xs) {
        if (inof(x - '0') == val) {
            ++ans.back().second;
            continue;
        }

        ans.emplace_back(inof(x - '0'), 1);
        val = inof(x - '0');
    }

    return ans;
}

string decode(const vector<pii> &cs) {
    string ans;

    for (const auto [val, num] : cs) {
        if (!num) continue;
        ans += string(num, static_cast<char>('0' + val));
    }

    return ans;
}

template <typename T> constexpr T div_ceil(const T x, const T y) {
    return x ? (1 + (x - 1) / y) : 0;
}

string end_state(const string &xs, const int m) {
    auto cs = encode(xs);
    if (sz(cs) == 1) return xs;

    for (int i = 0; i < sz(cs); ++i) {
        if (cs[i].first == 1) continue;

        if (i == 0) {
            const auto d = min(cs[i].second, m);

            cs[i].second -= d;
            cs[i + 1].second += d;
            continue;
        }

        if (i == sz(cs) - 1) {
            const auto d = min(cs[i].second, m);

            cs[i].second -= d;
            cs[i - 1].second += d;
            continue;
        }

        if (cs[i].second % 2 == 0) {
            const auto d = min(cs[i].second, 2 * m);
            cs[i].second -= d;
            cs[i - 1].second += div_ceil(d, 2);
            cs[i + 1].second += div_ceil(d, 2);
        } else {
            const auto d = min(cs[i].second - 1, 2 * m);
            cs[i].second -= d;
            cs[i - 1].second += div_ceil(d, 2);
            cs[i + 1].second += div_ceil(d, 2);
        }
    }

    return decode(cs);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        string xs(n, ' ');
        cin >> xs;
        cout << end_state(xs, m) << '\n';
    }

    return 0;
}
