#include <bits/stdc++.h>
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

using Card = pair<char, int>;

constexpr char chof(const int x) { return static_cast<char>(x); }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

Card parse_card(const string &s) {
    assert(sz(s) == 2);
    return {s[1], inof(s[0] - '0')};
}

string represent_card(const Card &c) {
    return string{chof(c.second + '0')} + string{c.first};
}

int cmp(const char trump, const Card a, const Card b) {
    if (a.first == trump && b.first != trump) return 1;
    if (a.first != trump && b.first == trump) return -1;

    if (a.first == b.first) {
        if (a.second > b.second) return 1;
        if (a.second < b.second) return -1;
    }

    return 0;
}

vector<vector<int>> less_than_graph(const char trump,
                                    const vector<Card> &cards) {
    const auto N = sz(cards);
    vector<vector<int>> g(N);
    for (int i = 0; i < N - 1; ++i) {
        for (int j = i + 1; j < N; ++j) {
            const auto c = cmp(trump, cards[i], cards[j]);
            if (c < 0) {
                g[i].push_back(j);
            } else if (c > 0) {
                g[j].push_back(i);
            }
        }
    }
    return g;
}

vector<pair<Card, Card>> game_plan(const char trump,
                                   const vector<Card> &cards) {
    assert(sz(cards) % 2 == 0);
    const int N = sz(cards);

    const auto g = less_than_graph(trump, cards);

    vector<bool> visited(N, false);
    vector<bool> used(N, false);
    vector<pair<Card, Card>> ans;

    const auto recur = [&](const auto self, const int p, const int u) -> void {
        const bool terminal =
            p >= 0 && all_of(cbegin(g[u]), cend(g[u]),
                             [&](const int v) { return used[v]; });
        if (terminal && !used[u] && !used[p]) {
            used[p] = true;
            used[u] = true;
            ans.emplace_back(cards[p], cards[u]);
            return;
        }

        for (const auto v : g[u]) {
            self(self, u, v);
        }
    };

    for (int u = 0; u < N; ++u) {
        if (!visited[u]) {
            recur(recur, -1, u);
        }
    }

    // cerr << ans << endl;

    return count(cbegin(used), cend(used), true) == N
               ? ans
               : vector<pair<Card, Card>>{};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string trump;
        cin >> trump;
        assert(sz(trump) == 1);

        vector<Card> xs;
        for (int i = 1; i <= 2 * n; ++i) {
            string s;
            cin >> s;
            xs.push_back(parse_card(s));
        }

        const auto ans = game_plan(trump[0], xs);
        if (empty(ans)) {
            cout << "IMPOSSIBLE\n";
        } else {
            assert(sz(ans) == n);
            for (const auto &[a, b] : ans) {
                cout << represent_card(a) << ' ' << represent_card(b) << '\n';
            }
        }
    }

    return 0;
}
