#include <bits/stdc++.h>
using namespace std;

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

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

void line_break() {
    string x;
    getline(cin, x);
}

static constexpr int AZ = 26;

vi gather_freqs(const string &xs) {
    vi ans(AZ, 0);
    for (const auto x : xs) ++ans[inof(x) - inof('A')];
    return ans;
}

string evolve(const map<pair<char, char>, char> &rules, const string &xs) {
    string ans;
    for (int i = 1; i < sz(xs); ++i) {
        const auto a = xs[i - 1];
        const auto b = xs[i];

        if (i == 1) ans += a;
        if (rules.count(pair{a, b})) {
            ans += rules.at(pair{a, b});
        }
        ans += b;
    }
    return ans;
}

int main() {
    string xs;
    cin >> xs;
    line_break();
    line_break();

    map<pair<char, char>, char> rules;

    for (string line; getline(cin, line);) {
        const auto parts = split(" -> ", line);
        rules[{parts[0][0], parts[0][1]}] = parts[1][0];
    }

    for (int i = 0; i < 10; ++i) xs = evolve(rules, xs);

    auto fs = gather_freqs(xs);
    sort(begin(fs), end(fs));
    fs.erase(remove(begin(fs), end(fs), 0), end(fs));
    cout << (fs.back() - fs[0]) << '\n';
    return 0;
}
