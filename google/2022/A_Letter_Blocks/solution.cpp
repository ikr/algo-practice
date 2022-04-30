#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <utility>
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

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

using Seq = pair<char, int>;

vector<Seq> encode(const string &xs) {
    vector<Seq> result;

    for (const auto x : xs) {
        if (!result.empty() && x == result.back().first) {
            ++(result.back().second);
        } else {
            result.emplace_back(x, 1);
        }
    }

    return result;
}

vector<vector<Seq>> encode(const vector<string> &xs) {
    vector<vector<Seq>> result;
    map<char, int> head_idx;
    map<char, int> tail_idx;
    map<char, int> rep_lengths;

    for (const auto &x : xs) {
        const auto ps = encode(x);

        if (sz(ps) == 1) {
            rep_lengths[ps[0].first] += ps[0].second;
        } else {
            head_idx[ps[0].first] = sz(result);
            tail_idx[ps.back().first] = sz(result);
            result.push_back(ps);
        }
    }

    for (const auto [c, l] : rep_lengths) {
        if (head_idx.count(c)) {
            const auto i = head_idx.at(c);
            result[i][0].second += l;
        } else if (tail_idx.count(c)) {
            const auto i = tail_idx.at(c);
            result[i].back().second += l;
        } else {
            result.push_back(vector{Seq{c, l}});
        }
    }

    return result;
}

string decode(const vector<Seq> &xs) {
    string result;
    for (const auto [c, l] : xs) {
        result += string(l, c);
    }
    return result;
}

string decode(const vector<vector<Seq>> &ss) {
    string result;
    for (const auto &s : ss) {
        result += decode(s);
    }
    return result;
}

bool is_showstopper(const vector<Seq> &xs) {
    set<char> seen;
    for (const auto [c, _] : xs) {
        if (seen.count(c)) return true;
        seen.insert(c);
    }
    return false;
}

string solve(const vector<string> &xs) {
    const auto ss = encode(xs);

    if (any_of(cbegin(ss), cend(ss), is_showstopper)) {
        return "IMPOSSIBLE";
    }

    map<char, int> head_idx;
    map<char, int> tail_idx;

    for (int i = 0; i < sz(ss); ++i) {
        if (head_idx.count(ss[i][0].first)) return "IMPOSSIBLE";
        head_idx[ss[i][0].first] = i;

        if (tail_idx.count(ss[i].back().first)) return "IMPOSSIBLE";
        tail_idx[ss[i].back().first] = i;
    }

    vector<vector<Seq>> result;
    vector<bool> visited(sz(ss), false);

    const auto dfs = [&](const auto self, const int u) -> void {
        visited[u] = true;
        result.push_back(ss[u]);

        const auto v = ss[u].back().first;
        if (head_idx.count(v) && !visited[head_idx.at(v)]) {
            self(self, head_idx.at(v));
        }
    };

    for (int u = 0; u < sz(ss); ++u) {
        if (!visited[u]) dfs(dfs, u);
    }

    return decode(result);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N;
        cin >> N;

        vector<string> xs(N);
        for (auto &x : xs) cin >> x;
        sort(begin(xs), end(xs));

        cout << "Case #" << i << ": " << solve(xs) << '\n';
    }

    return 0;
}
