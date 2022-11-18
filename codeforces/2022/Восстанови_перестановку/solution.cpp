#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> restore_perm(const vector<int> &B) {
    const int n = sz(B) * 2;
    vector<int> result;
    result.reserve(n);
    set<int> avail;

    {
        set<int> taken(cbegin(B), cend(B));
        for (int x = 1; x <= n; ++x) {
            if (!taken.contains(x)) avail.insert(x);
        }
    }

    for (const auto b : B) {
        if (avail.empty()) return {};

        const auto lo = *cbegin(avail);
        avail.erase(cbegin(avail));

        if (lo > b) return {};
        result.push_back(lo);
        result.push_back(b);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> B(n / 2);
        for (auto &b : B) cin >> b;

        const auto result = restore_perm(B);
        if (result.empty()) {
            cout << "-1\n";
        } else {
            cout << result << '\n';
        }
    }

    return 0;
}
