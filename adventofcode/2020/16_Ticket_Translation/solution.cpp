#include <bits/stdc++.h>
using namespace std;
using Range = pair<int, int>;
using ll = long long;

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

string your_ticket_line(const vector<string> &lines) {
    const auto header = find(cbegin(lines), cend(lines), "your ticket:");
    return *next(header);
}

void filter_out_invalid_tickets(const vector<Field> &fields,
                                vector<vector<int>> &nearby_tickets) {
    const auto is_valid_ticket = [&fields](const vector<int> &t) {
        for (const int x : t) {
            if (none_of(cbegin(fields), cend(fields),
                        [x](const auto &f) { return f.is_valid(x); })) {
                return true;
            }
        }

        return false;
    };

    nearby_tickets.erase(
        remove_if(begin(nearby_tickets), end(nearby_tickets), is_valid_ticket),
        cend(nearby_tickets));
}

set<int> complete_set(const int sz) {
    set<int> ans;
    for (int i = 0; i < sz; ++i) ans.insert(i);
    return ans;
}

pair<int, int> first_singleton(const vector<set<int>> &poss) {
    const int n = poss.size();

    for (int i = 0; i < n; ++i) {
        if (poss[i].size() == 1U) return {i, *poss[i].begin()};
    }

    return {-1, -1};
}

bool is_departure(const string &s) { return s.find("departure") == 0U; }

ll solve(const vector<Field> &fields, const vector<int> &your_ticket,
         vector<vector<int>> nearby_tickets) {
    filter_out_invalid_tickets(fields, nearby_tickets);

    const int n = fields.size();
    vector<set<int>> possibilities(n, complete_set(n));

    for (const auto &t : nearby_tickets) {
        for (int i = 0; i < n; ++i) {
            const int x = t[i];

            for (int j = 0; j < n; ++j) {
                if (!fields[j].is_valid(x)) {
                    possibilities[i].erase(j);
                }
            }
        }
    }

    vector<int> mappings(n, -1);

    for (;;) {
        const auto [i, x] = first_singleton(possibilities);
        if (i == -1) break;

        for (auto &xs : possibilities) {
            xs.erase(x);
        }

        mappings[i] = x;
    }

    ll ans = 1;

    for (int i = 0; i < n; ++i) {
        if (is_departure(fields[mappings[i]].m_name)) {
            ans *= your_ticket[i];
        }
    }

    return ans;
}

vector<int> parse_ticket(const string &line) {
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
              begin(nearby_tickets), parse_ticket);

    cout << solve(fields, parse_ticket(your_ticket_line(lines)), nearby_tickets)
         << '\n';
    return 0;
}
