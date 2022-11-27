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

int value_at_address_zero_after_program_ends(vector<int> xs, const int noun,
                                             const int verb) {
    xs[1] = noun;
    xs[2] = verb;

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

pair<int, int> find_proper_input(const vector<int> &xs, const int output) {
    for (int noun{}; noun <= 99; ++noun) {
        for (int verb{}; verb <= 99; ++verb) {
            const auto result =
                value_at_address_zero_after_program_ends(xs, noun, verb);
            if (result == output) {
                return {noun, verb};
            }
        }
    }

    return {-1, -1};
}

int integer_value(const string &x) { return stoi(x); }

int main() {
    string line;
    cin >> line;

    const auto tokens = split(",", line);
    vector<int> xs(sz(tokens));
    transform(cbegin(tokens), cend(tokens), begin(xs), integer_value);

    const auto [noun, verb] = find_proper_input(xs, 19690720);
    cout << (100 * noun + verb) << '\n';
    return 0;
}
