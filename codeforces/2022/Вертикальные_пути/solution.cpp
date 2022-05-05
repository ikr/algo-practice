#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<vector<int>> gather_children(const vector<int> &ps) {
    vector<vector<int>> ch(sz(ps));

    for (int i = 0; i < sz(ps); ++i) {
        if (ps[i] == i) continue;
        ch[ps[i]].push_back(i);
    }

    return ch;
}

int find_root(const vector<int> &ps) {
    for (int i = 0; i < sz(ps); ++i) {
        if (ps[i] == i) return i;
    }

    assert(false && "/o\\");
    return -1;
}

using pii = pair<int, int>;

priority_queue<pii> gather_levels(const vector<vector<int>> &ch,
                                  const int root) {
    priority_queue<pii> result;

    const auto recur = [&](const auto self, const int l, const int u) -> void {
        result.emplace(l, u);
        for (const auto v : ch[u]) {
            self(self, l + 1, v);
        }
    };

    recur(recur, 0, root);
    return result;
}

vector<vector<int>> minimal_path_partitions(const vector<int> &ps) {
    const auto ch = gather_children(ps);
    const auto root = find_root(ps);
    auto q = gather_levels(ch, root);

    vector<vector<int>> result;
    vector<bool> done(sz(ps), false);

    while (!q.empty()) {
        auto [_, u] = q.top();
        q.pop();
        if (done[u]) continue;

        vector<int> sub{u};
        done[u] = true;

        while (ps[u] != u && !done[ps[u]]) {
            sub.push_back(ps[u]);
            u = ps[u];
            done[u] = true;
        }

        reverse(begin(sub), end(sub));
        result.push_back(sub);
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

        vector<int> ps(n);
        for (auto &p : ps) {
            cin >> p;
            --p;
        }

        const auto paths = minimal_path_partitions(ps);
        cout << sz(paths) << '\n';

        for (const auto &path : paths) {
            cout << sz(path) << '\n';

            for (auto i = path.cbegin(); i != path.cend(); ++i) {
                if (i != path.cbegin()) cout << ' ';
                cout << ((*i) + 1);
            }

            cout << "\n\n";
        }
    }

    return 0;
}
