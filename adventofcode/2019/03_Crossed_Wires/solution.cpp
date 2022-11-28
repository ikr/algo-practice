#include <algorithm>
#include <bits/stdc++.h>
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

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr int manhattan(const pii a, const pii b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

pair<char, int> parse_command(const string &src) {
    return {src[0], stoi(src.substr(1))};
}

vector<pair<char, int>> parse_comma_separated_commands(const string &line) {
    const auto tokens = split(",", line);
    vector<pair<char, int>> result(sz(tokens));
    transform(cbegin(tokens), cend(tokens), begin(result), parse_command);
    return result;
}

pii destination_coord(const pii source, const pair<char, int> command) {
    const auto [ro, co] = source;
    switch (command.first) {
    case 'U':
        return {ro - command.second, co};

    case 'L':
        return {ro, co - command.second};

    case 'D':
        return {ro + command.second, co};

    case 'R':
        return {ro, co + command.second};

    default:
        assert(false && "Invalid direction");
    }
}

vector<pii> trace_with_origin_dropped(const vector<pair<char, int>> &commands) {
    vector<pii> result;

    for (const auto &command : commands) {
        result.push_back(destination_coord(
            result.empty() ? pii{0, 0} : result.back(), command));
    }

    return result;
}

pii closest_intersection(const vector<pair<char, int>> &commands_x,
                         const vector<pair<char, int>> &commands_y) {
    auto tx = trace_with_origin_dropped(commands_x);
    cerr << tx << endl;
    sort(begin(tx), end(tx));

    auto ty = trace_with_origin_dropped(commands_y);
    cerr << ty << endl;
    sort(begin(ty), end(ty));

    vector<pii> intersection;
    set_intersection(cbegin(tx), cend(tx), cbegin(ty), cend(ty),
                     back_inserter(intersection));
    assert(!intersection.empty());

    return *min_element(cbegin(intersection), cend(intersection),
                        [](const pii a, const pii b) {
                            return manhattan({0, 0}, a) < manhattan({0, 0}, b);
                        });
}

int main() {
    string line_x;
    cin >> line_x;
    const auto xs = parse_comma_separated_commands(line_x);

    string line_y;
    cin >> line_y;
    const auto ys = parse_comma_separated_commands(line_y);

    const auto [ro, co] = closest_intersection(xs, ys);
    cout << (ro + co) << '\n';
    return 0;
}
