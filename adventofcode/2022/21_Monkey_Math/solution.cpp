#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static constexpr int KEY_LENGTH = 4;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

ll root_value(const map<string, vector<string>> &expressions_by_key) {
    map<string, ll> memo;
    const auto recur = [&](const auto self, const string &key) -> ll {
        if (memo.contains(key)) return memo.at(key);
        return memo[key] = [&]() -> ll {
            const auto terms = expressions_by_key.at(key);
            if (sz(terms) == 1) return stoll(terms[0]);

            const auto a = self(self, terms[0]);
            const auto b = self(self, terms[2]);

            switch (terms[1][0]) {
            case '+':
                return a + b;
            case '-':
                return a - b;
            case '*':
                return a * b;
            case '/':
                return a / b;
            default:
                assert(false && "Unknown operation");
                return 0;
            }
        }();
    };

    return recur(recur, "root");
}

int main() {
    map<string, vector<string>> expressions_by_key;
    for (string line; getline(cin, line);) {
        const auto key = line.substr(0, KEY_LENGTH);
        const auto terms = split(" ", line.substr(KEY_LENGTH + 2));
        expressions_by_key.emplace(key, terms);
    }

    cout << root_value(expressions_by_key) << '\n';
    return 0;
}
