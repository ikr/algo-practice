#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
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

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> encode_verices() {
    string xs = "BGR";
    vector<string> result;

    do {
        result.push_back(xs);
    } while (next_permutation(begin(xs), end(xs)));

    assert(sz(result) == 6);
    return result;
}

int v_index(const vector<string> &evs, const string &s) {
    const auto it = find(cbegin(evs), cend(evs), s);
    assert(it != cend(evs));
    return inof(distance(cbegin(evs), it));
}

vvi build_graph(const vector<string> &evs) {
    vvi g(sz(evs));

    for (int u = 0; u < sz(g); ++u) {
        for (int i = 0; i <= 1; ++i) {
            for (int j = i + 1; j <= 2; ++j) {
                string buf = evs[u];
                swap(buf[i], buf[j]);

                const auto v = v_index(evs, buf);
                g[u].push_back(v);
            }
        }
    }

    return g;
}

bool is_possible(const string &s, const string &t) {
    const auto evs = encode_verices();
    const auto sv = v_index(evs, s);
    const auto tv = v_index(evs, t);
    const auto g = build_graph(evs);

    set<int> ds;
    const auto L_MAX = 7;

    function<void(int, int)> recur;
    recur = [&](const int curr_d, const int u) {
        if (curr_d == L_MAX) return;
        if (u == tv && curr_d) ds.insert(curr_d);

        for (const auto v : g[u]) {
            recur(curr_d + 1, v);
        }
    };

    recur(0, sv);
    cerr << ds << endl;

    const auto lo = *cbegin(ds);
    return (lo % 2) == 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string s;
    for (int i = 1; i <= 3; ++i) {
        char x;
        cin >> x;
        s += x;
    }

    string t;
    for (int i = 1; i <= 3; ++i) {
        char x;
        cin >> x;
        t += x;
    }

    cout << (is_possible(s, t) ? "Yes" : "No") << '\n';
    return 0;
}
