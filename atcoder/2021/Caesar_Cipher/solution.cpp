#include <bits/stdc++.h>
using namespace std;

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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr char chof(const int x) { return static_cast<char>(x); }

static constexpr int AZ = 26;

int dist(const char a, const char b) {
    int ans{};
    char aa = a;

    while (aa != b) {
        int x = inof(aa) - inof('a');
        ++x;
        x %= AZ;
        ++ans;
        aa = chof(x + inof('a'));
    }

    return ans;
}

bool can_shift(const string &s, const string &t) {
    vi xs(sz(s));
    transform(cbegin(s), cend(s), cbegin(t), begin(xs), dist);

    const int f = xs[0];
    return all_of(cbegin(xs), cend(xs), [f](const int x) { return x == f; });
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s;
    string t;
    cin >> s >> t;

    cout << (can_shift(s, t) ? "Yes" : "No") << '\n';
    return 0;
}
