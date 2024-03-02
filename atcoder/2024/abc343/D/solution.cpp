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

template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << '{';
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '(' << i->first << ' ' << i->second << ')';
    }
    os << '}';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, T;
    cin >> N >> T;

    map<ll, int> fq;
    fq.emplace(0, N);
    vector<ll> xs(N, 0);

    for (int t = 1; t <= T; ++t) {
        int A, B;
        cin >> A >> B;
        --A;

        // cerr << "xs: " << xs << " fq:" << fq << " A:" << A << " B:" << B
        //      << endl;

        ll old = xs[A];
        const auto it = fq.find(old);
        assert(it != cend(fq));
        if (it->second == 1) {
            fq.erase(it);
        } else {
            fq[old] = it->second - 1;
        }
        xs[A] += B;
        ++fq[old + B];
        cout << sz(fq) << '\n';
    }
    return 0;
}
