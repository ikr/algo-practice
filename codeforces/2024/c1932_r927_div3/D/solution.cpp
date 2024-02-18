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

const string Suits{"CDHS"};

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
    map<char, vector<Card>> by_suit;
    for (const auto &c : cards) {
        by_suit[c.first].push_back(c);
    }

    vector<pair<Card, Card>> ans;
    for (const auto &s : Suits) {
        sort(begin(by_suit[s]), end(by_suit[s]));

        if (s == trump) continue;
        while (sz(by_suit[s]) >= 2) {
            ans.emplace_back(by_suit[s][sz(by_suit[s]) - 2], by_suit[s].back());
            by_suit[s].pop_back();
            by_suit[s].pop_back();
        }
    }

    for (const auto &s : Suits) {
        if (s == trump) continue;
        while (!empty(by_suit[s]) && !empty(by_suit[trump])) {
            ans.emplace_back(by_suit[s].back(), by_suit[trump].back());
            by_suit[s].pop_back();
            by_suit[trump].pop_back();
        }
    }

    while (sz(by_suit[trump]) >= 2) {
        ans.emplace_back(by_suit[trump][sz(by_suit[trump]) - 2],
                         by_suit[trump].back());
        by_suit[trump].pop_back();
        by_suit[trump].pop_back();
    }

    bool ok = true;
    for (const auto &s : Suits) {
        if (!empty(by_suit[s])) {
            ok = false;
            break;
        }
    }
    return ok ? ans : vector<pair<Card, Card>>{};
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
