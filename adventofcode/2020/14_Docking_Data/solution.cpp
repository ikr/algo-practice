#include <bits/stdc++.h>
#include <variant>
using namespace std;
using ull = unsigned long long;

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

string reversed(string s) {
    reverse(begin(s), end(s));
    return s;
}

ull to_mask(const string &reversed_literal) {
    const ull n = reversed_literal.size();
    ull ans = ~0ULL;

    for (ull i = 0; i < n; ++i) {
        if (reversed_literal[i] != 'X') {
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

using Assignment = pair<int, ull>;
using Command = variant<Transformation, Assignment>;

Command parse_line(const string &line) {
    const string mask_prefix = "mask = ";
    if (line.substr(0, mask_prefix.size()) == mask_prefix) {
        return Transformation(line.substr(mask_prefix.size()));
    }

    const auto parts = split(regex("] = "), line);
    const string mem_prefix{"mem["};
    const auto address = parts[0].substr(mem_prefix.size());
    const auto value = parts[1];

    return Assignment{stoi(address), stoull(value)};
}

int main() {
    vector<Command> commands;

    for (string line; getline(cin, line);) {
        commands.push_back(parse_line(line));
    }

    vector<ull> mem(100000, 0ULL);
    Transformation curr_t;

    for (const auto c : commands) {
        match(
            c, [&](const Transformation &t) { curr_t = t; },
            [&](const Assignment &ab) {
                const auto [address, value] = ab;
                mem[address] = curr_t.apply(value);
            });
    }

    cout << accumulate(cbegin(mem), cend(mem), 0ULL) << '\n';
    return 0;
}
