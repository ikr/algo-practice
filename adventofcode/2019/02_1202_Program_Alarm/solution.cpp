#include <bits/stdc++.h>
using namespace std;

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int value_at_address_zero_after_program_ends(vector<int> xs) {
    xs[1] = 12;
    xs[2] = 2;

    for (int i = 0; i < sz(xs);) {
        const auto op = xs[i++];
        if (op == 99) break;

        const auto a = xs[xs[i++]];
        const auto b = xs[xs[i++]];
        const auto dst = xs[i++];

        if (op == 1) {
            xs[dst] = a + b;
        } else if (op == 2) {
            xs[dst] = a * b;
        } else {
            assert(false && "Wat?");
        }
    }

    return xs[0];
}

int integer_value(const string &x) { return stoi(x); }

int main() {
    string line;
    cin >> line;

    const auto tokens = split(",", line);
    vector<int> xs(sz(tokens));
    transform(cbegin(tokens), cend(tokens), begin(xs), integer_value);

    cout << value_at_address_zero_after_program_ends(move(xs)) << '\n';
    return 0;
}
