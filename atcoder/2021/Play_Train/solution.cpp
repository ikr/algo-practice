#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    return os;
}

vi restore_train(const vector<set<int>> &hd, const vector<set<int>> &tl,
                 const int u) {
    vi ans;

    function<void(const vector<set<int>> &, const int)> explore;
    explore = [&](const vector<set<int>> &g, const int uu) {
        ans.push_back(uu);
        for (const auto v : g[uu]) {
            explore(g, v);
        }
    };

    explore(hd, u);
    reverse(begin(ans), end(ans));
    ans.pop_back();

    explore(tl, u);
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n, q;
    cin >> n >> q;

    vector<set<int>> hd(n);
    vector<set<int>> tl(n);

    for (int i = 0; i < q; ++i) {
        int qtype;
        cin >> qtype;

        if (qtype == 1) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;

            hd[v].insert(u);
            tl[u].insert(v);
        } else if (qtype == 2) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;

            hd[v].erase(u);
            tl[u].erase(v);
        } else {
            assert(qtype == 3);
            int u;
            cin >> u;
            --u;

            const auto ans = restore_train(hd, tl, u);
            cout << sz(ans) << ' ';

            for (auto it = cbegin(ans); it != cend(ans); ++it) {
                if (it != cbegin(ans)) cout << ' ';
                cout << ((*it) + 1);
            }

            cout << '\n';
        }
    }

    return 0;
}
