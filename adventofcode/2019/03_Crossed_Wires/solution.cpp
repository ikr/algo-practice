#include <bits/stdc++.h>
using namespace std;

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

vector<pii> next_path_segment(const pii source, const pair<char, int> command) {
    const auto [dir, arg] = command;
    vector<pii> result;

    for (int i = 1; i <= arg; ++i) {
        const auto [ro, co] = result.empty() ? source : result.back();

        switch (dir) {
        case 'U':
            result.emplace_back(ro - 1, co);
            break;

        case 'L':
            result.emplace_back(ro, co - 1);
            break;

        case 'D':
            result.emplace_back(ro + 1, co);
            break;

        case 'R':
            result.emplace_back(ro, co + 1);
            break;

        default:
            assert(false && "Invalid direction");
        }
    }

    return result;
}

vector<pii> trace_with_origin_dropped(const vector<pair<char, int>> &commands) {
    vector<pii> result;

    for (const auto &command : commands) {
        const auto seg = next_path_segment(
            result.empty() ? pii{0, 0} : result.back(), command);
        result.insert(cend(result), cbegin(seg), cend(seg));
    }

    return result;
}

pii closest_intersection(const vector<pair<char, int>> &commands_x,
                         const vector<pair<char, int>> &commands_y) {
    auto tx = trace_with_origin_dropped(commands_x);
    sort(begin(tx), end(tx));

    auto ty = trace_with_origin_dropped(commands_y);
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

    const auto roco = closest_intersection(xs, ys);
    cout << manhattan({0, 0}, roco) << '\n';
    return 0;
}
