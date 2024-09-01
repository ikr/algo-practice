#include <atcoder/scc>
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

vector<int> values_of_f(const vector<int> &xs, const string &cl) {
    const auto n = sz(xs);
    atcoder::scc_graph g(n);

    for (int u = 0; u < n; ++u) {
        g.add_edge(u, xs[u]);
    }

    const auto cs = g.scc();
    // cerr << "\n\ncs:\n" << cs << endl;

    vector<int> component_index(n, -1);
    for (int i = 0; i < sz(cs); ++i) {
        for (const auto v : cs[i]) {
            assert(component_index[v] == -1);
            component_index[v] = i;
        }
    }

    map<int, int> blacks_by_component_index;
    for (int u = 0; u < n; ++u) {
        if (cl[u] == '0') {
            ++blacks_by_component_index[component_index[u]];
        }
    }

    vector<int> result(n, 0);
    for (int u = 0; u < n; ++u) {
        result[u] = blacks_by_component_index[component_index[u]];
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

        vector<int> xs(n);
        for (auto &x : xs) {
            cin >> x;
            --x;
        }

        string cl;
        cin >> cl;

        cout << values_of_f(xs, cl) << '\n';
    }

    return 0;
}
