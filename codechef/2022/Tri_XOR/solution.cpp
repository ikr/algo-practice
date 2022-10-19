#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const multiset<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

using tri = tuple<int, int, int>;

ostream &operator<<(ostream &os, const tri &x) {
    const auto [a, b, c] = x;
    os << '(' << a << ' ' << b << ' ' << c << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<tri> find_program(multiset<int> xs) {
    vector<tri> result;

    const auto zero_off_bit = [&](const int bit_shift) -> bool {
        const int mask = 1 << bit_shift;
        vector<int> stash;

        for (const auto x : xs) {
            if (x & mask) stash.push_back(x);
        }

        if (stash.empty()) return true;
        if (sz(stash) % 3) return false;

        for (auto i = 0; i < sz(stash); i += 3) {
            for (int j = 0; j < 3; ++j) {
                assert(i + j < sz(stash));
                const auto it = xs.find(stash[i + j]);
                assert(it != cend(xs));

                xs.erase(it);
            }

            xs.insert(stash[i] ^ stash[i + 1]);
            xs.insert(stash[i + 1] ^ stash[i + 2]);
            xs.insert(stash[i] ^ stash[i + 2]);
            result.emplace_back(stash[i], stash[i + 1], stash[i + 2]);
        }

        return true;
    };

    for (int bs = 31; bs >= 0; --bs) {
        if (!zero_off_bit(bs)) {
            // cerr << "On bs: " << bs << " rest: " << xs << " program: " <<
            // result
            //      << endl;
            assert(false && "zero-off failed");
        }
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

        vector<int> xs;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            if (x) xs.push_back(x);
        }

        const auto ops = find_program(multiset<int>(crbegin(xs), crend(xs)));
        cout << sz(ops) << '\n';
        for (const auto &[a, b, c] : ops) {
            cout << a << ' ' << b << ' ' << c << '\n';
        }
    }

    return 0;
}
