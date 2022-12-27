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

ll root_argument_a(const map<string, vector<string>> &expressions_by_key,
                   const ll humn_value) {
    map<string, ll> memo;
    const auto recur = [&](const auto self, const string &key) -> ll {
        if (memo.contains(key)) return memo.at(key);
        return memo[key] = [&]() -> ll {
            if (key == "humn") return humn_value;
            const auto terms = expressions_by_key.at(key);
            if (sz(terms) == 1) return stoll(terms[0]);

            const auto a = self(self, terms[0]);
            const auto b = self(self, terms[2]);
            if (key == "root") {
                cerr << "a:" << a << " b:" << b << " delta:" << a - b << endl;
                return a;
            }

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

    ll lo = 3759569926100LL;
    assert(root_argument_a(expressions_by_key, lo) >= 0LL);
    // ll hi = 125000000000000LL;
    // assert(root_argument_a(expressions_by_key, hi) < 0LL);

    // while (lo + 1 < hi) {
    //     const auto mid = midpoint(lo, hi);
    //     if (root_argument_a(expressions_by_key, lo) > 0LL) {
    //         lo = mid;
    //     } else {
    //         hi = mid;
    //     }
    // }

    return 0;
}
