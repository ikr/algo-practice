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
    const auto ss = [&]() -> vector<vector<Seq>> {
        vector<vector<Seq>> result(sz(xs));
        transform(cbegin(xs), cend(xs), begin(result), encode);
        return result;
    }();

    if (any_of(cbegin(ss), cend(ss), is_showstopper)) {
        cerr << "showstopper" << endl;
        return "IMPOSSIBLE";
    }

    const auto proto = [&]() -> set<int> {
        set<int> result;
        for (int i = 0; i < sz(xs); ++i) result.insert(i);
        return result;
    }();

    const auto mids = [&]() -> map<char, vector<int>> {
        map<char, vector<int>> result;
        for (int i = 0; i < sz(ss); ++i) {
            if (sz(ss[i]) == 1) {
                result[ss[i][0].first].push_back(i);
            }
        }
        return result;
    }();

    map<char, int> heads;
    map<char, int> tails;

    for (int i = 0; i < sz(ss); ++i) {
        if (sz(ss[i]) > 1) {
            heads[ss[i][0].first] = i;
            tails[ss[i].back().first] = i;
        }
    }

    for (int first = 0; first < sz(xs); ++first) {
        vector<vector<Seq>> result{ss[first]};
        auto rem = proto;
        rem.erase(first);

        char cur = ss[first].back().first;
        for (;;) {
            if (mids.count(cur)) {
                for (const auto j : mids.at(cur)) {
                    result.push_back(ss[j]);
                    rem.erase(j);
                }
            }

            if (!heads.count(cur)) break;
            result.push_back(ss[heads.at(cur)]);
            rem.erase(heads.at(cur));
            cur = ss[heads.at(cur)].back().first;
        }

        cerr << "first:" << first << " result:" << result << " rem:" << rem
             << endl;

        if (rem.empty()) return decode(result);
    }

    return "IMPOSSIBLE";
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

        cout << "Case #" << i << ": " << solve(xs) << '\n';
    }

    return 0;
}
