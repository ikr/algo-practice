#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<int> &A, const vector<int> &B,
                 const vector<int> &D) {
    multiset<int> ds(cbegin(D), cend(D));
    const set<int> bs(cbegin(B), cend(B));

    multiset<int> overwritten;
    for (int i = 0; i < sz(A); ++i) {
        if (A[i] != B[i]) {
            if (!ds.contains(B[i])) return false;
            overwritten.insert(B[i]);
        }
    }

    if (!bs.contains(D.back())) return false;

    for (const auto d : overwritten) {
        const auto it = ds.find(d);
        if (it == cend(ds)) return false;
        ds.erase(it);
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> A(n);
        for (auto &a : A) cin >> a;

        vector<int> B(n);
        for (auto &b : B) cin >> b;

        int m;
        cin >> m;

        vector<int> D(m);
        for (auto &d : D) cin >> d;

        cout << (is_possible(A, B, D) ? "YES" : "NO") << '\n';
    }

    return 0;
}
