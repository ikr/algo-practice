#include <bits/stdc++.h>
using namespace std;

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

double
root_arguments_diff(const map<string, vector<string>> &expressions_by_key,
                    const double humn_value) {
    map<string, double> memo;
    const auto recur = [&](const auto self, const string &key) -> double {
        if (memo.contains(key)) return memo.at(key);
        return memo[key] = [&]() -> double {
            if (key == "humn") return humn_value;
            const auto terms = expressions_by_key.at(key);
            if (sz(terms) == 1) return stod(terms[0]);

            const auto a = self(self, terms[0]);
            const auto b = self(self, terms[2]);
            if (key == "root") {
                cerr << "a:" << a << " b:" << b << " delta:" << a - b << endl;
                return a - b;
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
    cerr << setprecision(2) << fixed;

    map<string, vector<string>> expressions_by_key;
    for (string line; getline(cin, line);) {
        const auto key = line.substr(0, KEY_LENGTH);
        const auto terms = split(" ", line.substr(KEY_LENGTH + 2));
        expressions_by_key.emplace(key, terms);
    }

    double lo = 0;
    assert(root_arguments_diff(expressions_by_key, lo) > 0);
    double hi = 1e16;
    assert(root_arguments_diff(expressions_by_key, hi) < 0);

    for (int i = 0; i < 100; ++i) {
        const auto mid = midpoint(lo, hi);
        cerr << "mid:" << mid << endl;
        if (root_arguments_diff(expressions_by_key, mid) >= 0) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    return 0;
}
