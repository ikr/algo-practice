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

template <typename T> ostream &operator<<(ostream &os, const set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool brute_force(const vector<ll> &xs) {
    const auto n = sz(xs);
    if (n == 1) return true;

    const auto ev_sum = [&](const int i, const int j) -> ll {
        assert(i <= j && 0 <= i && j < n);
        ll result{};
        for (int k = i; k <= j; ++k) {
            if (k % 2 == 0) result += xs[k];
        }
        return result;
    };

    const auto od_sum = [&](const int i, const int j) -> ll {
        assert(i <= j && 0 <= i && j < n);
        ll result{};
        for (int k = i; k <= j; ++k) {
            if (k % 2) result += xs[k];
        }
        return result;
    };

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (ev_sum(i, j) == od_sum(i, j)) return true;
        }
    }

    return false;
}

bool is_possible(const vector<ll> &xs) {
    const auto n = sz(xs);
    if (n == 1) return false;

    vector<ll> evs(n, 0);
    vector<ll> ods(n, 0);
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            evs[i] = xs[i];
        } else {
            ods[i] = xs[i];
        }
    }

    vector<ll> ess(n);
    partial_sum(cbegin(evs), cend(evs), begin(ess));
    vector<ll> oss(n);
    partial_sum(cbegin(ods), cend(ods), begin(oss));
    // cerr << "ess:" << ess << " oss:" << oss << endl;

    set<ll> dif;

    for (int i = 0; i < n; ++i) {
        if (i && xs[i - 1] == xs[i]) return true;
        if (oss[i] == ess[i]) return true;
        const auto cur = oss[i] - ess[i];
        if (dif.contains(cur)) {
            // cerr << "i:" << i << " dif:" << dif << endl;
            return true;
        }
        if (i > 1) dif.insert(oss[i - 2] - ess[i - 2]);
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<ll> xs(n);
        for (auto &x : xs) cin >> x;

        // assert(is_possible(xs) == brute_force(xs));
        cout << (is_possible(xs) ? "YES" : "NO") << '\n';
    }

    return 0;
}
