#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

string reversed(string s) {
    reverse(begin(s), end(s));
    return s;
}

ull to_mask(const string &reversed_literal) {
    const int n = reversed_literal.size();
    ull ans = ~0ULL;

    for (int i = 0; i < n; ++i) {
        if (reversed_literal[i] != 'X') {
            ans = ans & ~(1 << i);
        }
    }

    return ans;
}

ull to_forced_value(const string &reversed_literal) {
    const int n = reversed_literal.size();
    ull ans = 0ULL;

    for (int i = 0; i < n; ++i) {
        if (reversed_literal[i] == '1') {
            ans |= (1 << i);
        }
    }

    return ans;
}

struct Transformation final {
    ull apply(const ull x) const { return (x & m_mask) | m_forced_value; }

    Transformation(string literal) : m_mask{0}, m_forced_value{0} {
        reverse(begin(literal), end(literal));
        m_mask = to_mask(literal);
        m_forced_value = to_forced_value(literal);
    }

  private:
    ull m_mask;
    ull m_forced_value;
};

int main() {
    for (string line; getline(cin, line);) {
    }
    return 0;
}
