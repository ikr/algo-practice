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

string unique_chars(const string &xs) {
    set<char> xss(cbegin(xs), cend(xs));
    string ans(sz(xss), ' ');
    copy(cbegin(xss), cend(xss), begin(ans));
    return ans;
}

vector<set<int>> letter_indices(const string &xs) {
    vector<set<int>> ans(26);
    for (int i = 0; i < sz(xs); ++i) ans[xs[i] - 'a'].insert(i);
    return ans;
}

string max_str(const string &xs) {
    const auto idx = letter_indices(xs);

    vi placement(26, -1);
    for (int i = sz(idx) - 1; i >= 0; --i) {
        if (idx[i].empty()) continue;

        for (int j = i + 1; j < sz(idx); ++j) {
            if (idx[j].empty()) continue;
            const auto it = idx[i].upper_bound(placement[j]);

            if (it != cend(idx[i])) {
                placement[i] = max(placement[i], *it);
            }
        }

        if (placement[i] == -1) placement[i] = *cbegin(idx[i]);
    }

    string ans = unique_chars(xs);
    sort(begin(ans), end(ans), [&placement](const char x, const char y) {
        return placement[x - 'a'] < placement[y - 'a'];
    });

    cerr << ans << '\n';
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    assert(max_str("codeforces") == "odfrces");
    assert(max_str("aezakmi") == "ezakmi");
    assert(max_str("abacaba") == "cba");
    assert(max_str("convexhull") == "convexhul");
    assert(max_str("swflldjgpaxs") == "wfldjgpaxs");
    assert(max_str("myneeocktxpqjpz") == "myneocktxqjpz");
    assert(max_str("jpimokmwii") == "jpokmwi");
    assert(max_str("gqeojmgfpguxiu") == "qeojmgfpxiu");

    int t;
    cin >> t;
    while (t--) {
        string xs;
        cin >> xs;
        cout << max_str(xs) << '\n';
    }

    return 0;
}
