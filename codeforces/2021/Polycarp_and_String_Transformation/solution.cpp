#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int SZ = inof('z') - inof('a') + 1;

string removal_seq(const string &t) {
    vector<bool> seen(SZ, false);
    string ans;

    for (auto it = crbegin(t); it != crend(t); ++it) {
        const int i = inof(*it) - inof('a');

        if (!seen[i]) {
            seen[i] = true;
            ans.push_back(*it);
        }
    }

    reverse(begin(ans), end(ans));
    return ans;
}

int index_of_complete_occurance(const string &needle, const string &haystack) {
    set<char> xs(cbegin(needle), cend(needle));
    int i = 0;

    for (;;) {
        xs.erase(haystack[i]);
        if (xs.empty()) break;
        ++i;
    }

    return i;
}

bool verify(string s, const string &xs, const string &t) {
    string buf;
    for (const auto x : xs) {
        buf += s;
        s.erase(remove(begin(s), end(s), x), end(s));
    }

    return buf == t;
}

pair<string, string> s_and_removal_seq(const string &t) {
    const auto xs = removal_seq(t);
    const auto edge =
        max(index_of_complete_occurance(xs, t), inof(t.rfind(xs[0])));

    string needle = t.substr(0, edge);
    needle.erase(remove(begin(needle), end(needle), xs[0]), end(needle));

    const auto i = t.find(needle, edge + 1);
    const auto s = t.substr(0, i);

    return verify(s, xs, t) ? pair{s, xs} : pair{string{""}, string{""}};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int T;
    cin >> T;
    while (T--) {
        string t;
        cin >> t;

        const auto [s, xs] = s_and_removal_seq(t);
        if (xs.empty()) {
            cout << "-1\n";
        } else {
            cout << s << ' ' << xs << '\n';
        }
    }

    return 0;
}
