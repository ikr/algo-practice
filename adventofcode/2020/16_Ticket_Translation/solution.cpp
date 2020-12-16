#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
using Range = pair<int, int>;

vector<string> split(const regex &delim, const string &s) {
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), delim, -1),
                          sregex_token_iterator{});
}

struct Field final {
    Field(const string &name, const Range &r1, const Range &r2)
        : m_name{name}, m_r1{r1}, m_r2{r2} {}

    Field() {}

    bool is_valid(const int x) const {
        const auto [a, b] = m_r1;
        const auto [c, d] = m_r2;
        return (a <= x && x <= b) || (c <= x && x <= d);
    }

    string m_name;
    Range m_r1;
    Range m_r2;
};

Range parse_range(const string &literal) {
    const auto parts = split(regex("-"), literal);
    return {stoi(parts[0]), stoi(parts[1])};
}

string drop_last(string s) {
    const int sz = s.size();
    return s.substr(0, sz - 1);
}

Field parse_field(const string &line) {
    const auto top_parts = split(regex(": "), line);
    const auto range_parts = split(regex(" "), top_parts[1]);

    return Field(drop_last(top_parts[0]), parse_range(range_parts[0]),
                 parse_range(range_parts[2]));
}

vector<string> gather_fields_block(const vector<string> &lines) {
    return vector<string>(cbegin(lines), find(cbegin(lines), cend(lines), ""));
}

vector<string> gather_nearby_tickets_block(const vector<string> &lines) {
    const auto header = find(cbegin(lines), cend(lines), "nearby tickets:");
    return vector<string>(next(header), cend(lines));
}

int solve(const vector<Field> &fields,
          const vector<vector<int>> &nearby_tickets) {

    int ans = 0;

    for (const auto &xs : nearby_tickets) {
        for (const int x : xs) {
            if (none_of(cbegin(fields), cend(fields),
                        [x](const auto &f) { return f.is_valid(x); })) {
                ans += x;
            }
        }
    }

    return ans;
}

vector<int> parse_tickets(const string &line) {
    const auto tokens = split(regex(","), line);
    vector<int> ans(tokens.size());
    transform(cbegin(tokens), cend(tokens), begin(ans),
              [](const string &s) { return stoi(s); });
    return ans;
}

int main() {
    vector<string> lines;

    for (string line; getline(cin, line);) {
        lines.push_back(line);
    }

    const auto fields_block = gather_fields_block(lines);
    vector<Field> fields(fields_block.size());
    transform(cbegin(fields_block), cend(fields_block), begin(fields),
              parse_field);

    const auto nearby_tickets_block = gather_nearby_tickets_block(lines);
    vector<vector<int>> nearby_tickets(nearby_tickets_block.size());
    transform(cbegin(nearby_tickets_block), cend(nearby_tickets_block),
              begin(nearby_tickets), parse_tickets);

    cout << solve(fields, nearby_tickets) << '\n';
    return 0;
}
