#include <bits/stdc++.h>
using namespace std;

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

using ull = unsigned long long;
using vi = vector<int>;
using iter = list<int>::const_iterator;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static const list<int> null_list;
static const int INF = 1e9 + 10;

struct ChainLink final {
    int v;
    iter it;

    ChainLink(const int v_, const iter it_) : v{v_}, it{it_} {}
    // ChainLink() : v{0}, it{cend(null_list)} {}
    // ChainLink(const ChainLink &o) : v(o.v), it(o.it) {}

    // ChainLink &operator=(const ChainLink &o) {
    //     if (&o == this) return *this;
    //     v = o.v;
    //     it = o.it;
    //     return *this;
    // }
};

struct ChainLinkLess final {
    bool operator()(const ChainLink &a, const ChainLink &b) const {
        return pair{a.v, reinterpret_cast<ull>(&(*a.it))} <
               pair{b.v, reinterpret_cast<ull>(&(*b.it))};
    }
};

struct ChainLinkGreater final {
    bool operator()(const ChainLink &a, const ChainLink &b) const {
        return pair{a.v, reinterpret_cast<ull>(&(*a.it))} >
               pair{b.v, reinterpret_cast<ull>(&(*b.it))};
    }
};

bool is_first(const list<int> &xs, const iter it) { return it == cbegin(xs); }

bool is_last(const list<int> &xs, const iter it) {
    return it == prev(cend(xs));
}

vi lo_by_length(list<int> xs) { return {-1, -1, -1, -1}; }

vi hi_by_length(list<int> xs) {
    const int n = sz(xs);
    map<int, int> freqs;
    multiset<ChainLink, ChainLinkLess> pq;

    for (auto [it, i] = pair{cbegin(xs), 0}; it != cend(xs); ++it, ++i) {
        int key = INF;

        if (i != 0) {
            const auto pit = prev(it);
            if (abs(*it - *pit) < 2) {
                key = min(key, 0);
            } else {
                key = min(key, max(*it, *pit) - 1);
            }

            ++freqs[key];
        }

        if (i != n - 1) {
            const auto nit = next(it);
            if (abs(*it - *nit) < 2) {
                key = min(key, 0);
            } else {
                key = min(key, max(*it, *nit) - 1);
            }
        }

        pq.emplace(key, it);
    }

    int curr = INF;
    for (const auto [v, f] : freqs) {
        curr = min(curr, v);
    }

    const auto step_down = [&]() {
        assert(sz(xs) > 2);

        const auto [v, it] = *next(cbegin(pq));
        pq.erase(next(cbegin(pq)));

        const auto neigh = [&](const iter ii) -> vector<iter> {
            vector<iter> ans;
            if (!is_first(xs, ii)) ans.push_back(prev(ii));
            if (!is_last(xs, ii)) ans.push_back(next(ii));
            return ans;
        }(it);

        for (const auto it_ : neigh) {
            const int a = (abs(*it - *it_) < 2) ? 0 : max(*it, *it_) - 1;

            --freqs[a];
            if (!freqs[a]) freqs.erase(a);
        }

        if (sz(neigh) == 2) {
            const auto jt = neigh[0];
            const auto kt = neigh[1];

            if (abs(*jt - *kt) < 2) {
                ++freqs[0];
            } else {
                ++freqs[max(*jt, *kt) - 1];
            }
        }
        curr = cbegin(freqs)->first;
        xs.erase(it);
    };

    int k = n;
    vi ans(n + 1, -1);
    if (curr) ans[k] = curr;

    do {
        step_down();
        --k;
        if (curr) ans[k] = curr;
    } while (k > 2);

    return ans;
}

void print_from_2nd(const vi &xs) {
    for (int i = 2; i < sz(xs); ++i) {
        cout << xs[i];
        if (i != sz(xs) - 1) cout << ' ';
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        list<int> xs;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            xs.push_back(x);
        }

        print_from_2nd(lo_by_length(xs));
        print_from_2nd(hi_by_length(xs));
    }

    return 0;
}
