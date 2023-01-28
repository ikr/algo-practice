#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr bool match(const char a, const char b) {
    return (a == '?' || b == '?') || a == b;
}

set<int> gather_bad_indices(const string &a, const string &b) {
    assert(sz(a) == sz(b));
    set<int> ans;
    for (int i = 0; i < sz(a); ++i) {
        if (!match(a[i], b[i])) ans.insert(i);
    }
    return ans;
}

vector<bool> solve(const string &S, const string &T) {
    vector<bool> ans;
    ans.reserve(sz(T) + 1);

    auto xs = S.substr(sz(S) - sz(T));
    assert(sz(xs) == sz(T));

    auto bi = gather_bad_indices(xs, T);
    ans.push_back(bi.empty());

    for (int k = 1; k <= sz(T); ++k) {
        const auto i = k - 1;
        xs[i] = S[i];

        if (match(xs[i], T[i])) {
            bi.erase(i);
        } else {
            bi.insert(i);
        }

        ans.push_back(bi.empty());
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string S, T;
    cin >> S >> T;

    for (const auto yes : solve(S, T)) {
        cout << (yes ? "Yes" : "No") << '\n';
    }
    return 0;
}
