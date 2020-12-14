#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;

string reversed(string s) {
    reverse(begin(s), end(s));
    return s;
}

ull to_mask(const string &reversed_literal) {}

struct Transformation final {
    ull apply(const ull x) const { return (x & m_mask) | m_forced_value; }

    Transformation(string literal) {}

  private:
    ull m_mask;
    ull m_forced_value;
};

int main() {
    for (string line; getline(cin, line);) {
    }
    return 0;
}
