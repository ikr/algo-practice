#include <bits/stdc++.h>
#include <variant>
using namespace std;
using ull = unsigned long long;
using ui = unsigned int;

template <class... Ts> struct overloaded final : Ts... {
    using Ts::operator()...;
};

template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

template <typename Variant, typename... Matchers>
auto match(Variant &&variant, Matchers &&... matchers) {
    return visit(overloaded{forward<Matchers>(matchers)...},
                 forward<Variant>(variant));
}

vector<string> split(const regex &delim, const string &s) {
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), delim, -1),
                          sregex_token_iterator{});
}

ull to_mask(const string &reversed_literal) {
    const ull n = reversed_literal.size();
    ull ans = ~0ULL;

    for (ull i = 0; i < n; ++i) {
        if (reversed_literal[i] != '.') {
            ans = ans & ~(1ULL << i);
        }
    }

    return ans;
}

ull to_forced_value(const string &reversed_literal) {
    const ull n = reversed_literal.size();
    ull ans = 0ULL;

    for (ull i = 0; i < n; ++i) {
        if (reversed_literal[i] == '1') {
            ans |= (1ULL << i);
        }
    }

    return ans;
}

vector<string> generate_instances(const string &pattern) {
    const int n = pattern.size();

    vector<int> x_indices;
    for (int i = 0; i < n; ++i) {
        if (pattern[i] == 'X') x_indices.push_back(i);
    }

    if (x_indices.empty()) return {pattern};
    const ui sz = x_indices.size();

    vector<string> ans;
    ans.reserve(1U << sz);
    for (ui i = 0U; i < (1U << sz); ++i) {
        bitset<32> bs{i};

        string s{pattern};
        for (ui j = 0; j < sz; ++j) {
            s[x_indices[j]] = bs.test(j) ? '1' : '0';
        }
        ans.push_back(s);
    }
    return ans;
}

struct Transformation final {
    ull apply(const ull x) const { return (x & m_mask) | m_forced_value; }

    Transformation() : m_mask{~0ULL}, m_forced_value{0ULL} {}

    explicit Transformation(string literal) : m_mask{0}, m_forced_value{0} {
        reverse(begin(literal), end(literal));
        m_mask = to_mask(literal);
        m_forced_value = to_forced_value(literal);
    }

  private:
    ull m_mask;
    ull m_forced_value;
};

struct AssignmentScheme final {
    AssignmentScheme() : m_literal{"...................................."} {}
    explicit AssignmentScheme(const string &literal) : m_literal{literal} {}

    void apply(unordered_map<ull, ull> &mem, const ull address,
               const ull value) {
        for (const auto &instance : generate_instances(m_literal)) {
            const Transformation t{instance};
            mem[t.apply(address)] = value;
        }
    }

  private:
    string m_literal;
};

using Assignment = pair<ull, ull>;
using Command = variant<AssignmentScheme, Assignment>;

string translate_literal(string literal) {
    transform(cbegin(literal), cend(literal), begin(literal),
              [](const char c) { return c == '0' ? '.' : c; });
    return literal;
}

Command parse_line(const string &line) {
    const string mask_prefix = "mask = ";
    if (line.substr(0, mask_prefix.size()) == mask_prefix) {
        const auto raw_literal = line.substr(mask_prefix.size());
        return AssignmentScheme(translate_literal(raw_literal));
    }

    const auto parts = split(regex("] = "), line);
    const string mem_prefix{"mem["};
    const auto address = parts[0].substr(mem_prefix.size());
    const auto value = parts[1];

    return Assignment{stoull(address), stoull(value)};
}

int main() {
    vector<Command> commands;

    for (string line; getline(cin, line);) {
        commands.push_back(parse_line(line));
    }

    unordered_map<ull, ull> mem;
    AssignmentScheme curr_sch;

    for (const auto c : commands) {
        match(
            c, [&](const AssignmentScheme &sch) { curr_sch = sch; },

            [&](const Assignment &ab) {
                const auto [address, value] = ab;
                curr_sch.apply(mem, address, value);
            });
    }

    cout << accumulate(
                cbegin(mem), cend(mem), 0ULL,
                [](const ull agg, const auto &el) { return agg + el.second; })
         << '\n';
    return 0;
}
