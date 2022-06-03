#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
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

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int initial_vertex(const int n, const vector<pii> &edges,
                   const set<int> &pots) {
    // cerr << "edges: " << edges << endl;

    vector<vector<int>> g(n);
    for (const auto [u, v] : edges) {
        g[v].push_back(u);
    }

    // cerr << g << endl;

    for (int u = 0; u < n; ++u) {
        if (g[u].empty() && pots.count(u)) return u;
    }

    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        int v_num{};
        map<string, int> idx;
        set<int> pots;
        map<int, string> idx1;

        const auto v_index = [&](const string &a) -> int {
            const auto it = idx.find(a);
            if (it == cend(idx)) {
                const auto result = v_num++;
                idx.emplace(a, result);
                if (sz(a) == 1) {
                    pots.insert(result);
                    idx1.emplace(result, a);
                }
                return result;
            }

            return it->second;
        };

        vector<pii> edges;

        for (int i = 1; i <= n; ++i) {
            string a, b;
            cin >> a >> b;

            if (sz(a) == 1 || sz(b) == 1) {
                edges.emplace_back(v_index(a), v_index(b));
            }
        }

        string s;
        cin >> s;

        cout << idx1[initial_vertex(v_num, edges, pots)] << '\n';
    }

    return 0;
}
