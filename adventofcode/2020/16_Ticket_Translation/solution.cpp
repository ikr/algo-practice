#include <bits/stdc++.h>
using namespace std;
using Range = pair<int, int>;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

vector<string> split(const regex &delim, const string &s) {
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), delim, -1),
                          sregex_token_iterator{});
}

struct Field final {
    Field(const string &name, const Range &r1, const Range &r2)
        : m_name{name}, m_r1{r1}, m_r2{r2} {}

    Field() {}

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
    const auto parts = split(regex(" "), line);
    cout << "parts:" << parts << '\n';
    return Field(drop_last(parts[0]), parse_range(parts[1]),
                 parse_range(parts[3]));
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
    return 0;
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

    return 0;
}
