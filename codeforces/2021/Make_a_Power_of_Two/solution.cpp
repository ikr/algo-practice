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
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> powers_of_2() {
    vector<string> ans;

    for (int i = 0; i <= 62; ++i) {
        const ll x = (1LL << i);
        stringstream ss;
        ss << x;
        ans.push_back(ss.str());
    }

    return ans;
}

int longest_subseq_match(const string &needle, const string &haystack) {
    int ans = 0;

    string::size_type i = 0;
    string::size_type j = 0;
    while (i < needle.size() && j < haystack.size() &&
           haystack.find(needle[i], j) != string::npos) {
        j = haystack.find(needle[i], j) + 1;
        ++i;
        ++ans;
    }

    return ans;
}

int min_ops(const vector<string> &ps, const string &x) {
    int ans = sz(x) + 1;

    for (const auto &p : ps) {
        const auto m = longest_subseq_match(p, x);
        ans = min(ans, sz(x) - m + sz(p) - m);
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    const auto ps = powers_of_2();

    int t;
    cin >> t;
    while (t--) {
        string n;
        cin >> n;
        cout << min_ops(ps, n) << '\n';
    }

    return 0;
}
