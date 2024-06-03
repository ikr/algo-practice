#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool is_possible(const vector<int> &A, const vector<int> &B,
                 const vector<int> &D) {
    multiset<int> rem(cbegin(D), cend(D));

    for (int i = 0; i < sz(A); ++i) {
        if (A[i] == B[i]) continue;

        const auto it = rem.find(B[i]);
        if (it == cend(rem)) return false;
        rem.erase(it);
    }

    const set<int> bs(cbegin(B), cend(B));

    for (const auto r : rem) {
        if (!bs.contains(r)) return false;
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
