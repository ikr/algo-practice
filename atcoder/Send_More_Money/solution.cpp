#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

string all_letters(const vector<string> &codes) {
    set<char> ls;
    for (const auto &code : codes) {
        ls.insert(cbegin(code), cend(code));
    }

    string ans(sz(ls), ' ');
    copy(cbegin(ls), cend(ls), begin(ans));
    return ans;
}

using Tri = tuple<ll, ll, ll>;
static constexpr Tri NOPE{-1, -1, -1};

void complete_to_10(string &ls) {
    for (int i = 0; i < 11 && sz(ls) < 10; ++i) {
        ls += static_cast<char>('A' + i);
    }
}

map<char, int> to_table(const string &pad) {
    map<char, int> ans;

    for (int i = 0; i < 10; ++i) {
        ans[pad[i]] = i;
    }

    return ans;
}

ll interpret(const map<char, int> &tbl, const string &code) {
    ll ans{};

    for (int i = 0; i < sz(code); ++i) {
        ans *= 10LL;
        ans += tbl.at(code[i]);
    }

    return ans;
}

Tri suggest_interpretation(const string &code1, const string &code2,
                           const string &code3) {
    auto ls = all_letters({code1, code2, code3});
    if (sz(ls) > 10) return NOPE;
    complete_to_10(ls);
    sort(begin(ls), end(ls));

    do {
        const auto tbl = to_table(ls);
        const ll x = interpret(tbl, code1);
        const ll y = interpret(tbl, code2);
        const ll z = interpret(tbl, code3);

        if (x > 0 && y > 0 && x + y == z) return {x, y, z};
    } while (next_permutation(begin(ls), end(ls)));

    return NOPE;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string code1, code2, code3;
    cin >> code1 >> code2 >> code3;

    const auto [x, y, z] = suggest_interpretation(code1, code2, code3);

    if (x == -1) {
        cout << "UNSOLVABLE\n";
    } else {
        cout << x << '\n' << y << '\n' << z << '\n';
    }

    return 0;
}
