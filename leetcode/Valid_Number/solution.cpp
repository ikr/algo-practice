#include<bits/stdc++.h>
using namespace std;

void ltrim(string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return ch != ' '; }));
}

void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return ch != ' ';
    }).base(), s.end());
}

void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

bool confirm_match(const string &pattern, const string &input) {
    smatch m;
    regex_match(input, m, regex{pattern});
    return m.size() && m[0].matched;
}

struct Solution {
    bool isNumber(string s) const {
        trim(s);

        return confirm_match("^[+-]?[0-9]+(\\.[0-9]*)?(e[+-]?[0-9]+)?$", s) ||
            confirm_match("^[+-]?\\.[0-9]+(e[+-]?[0-9]+)?$", s);
    }
};

static const vector<pair<string, bool>> test_cases{
    {"0", true},
    {" 0.1 ", true},
    {"abc", false},
    {"1 a", false},
    {"2e10", true},
    {" -90e3   ", true},
    {" 1e", false},
    {"e3", false},
    {" 6e-1", true},
    {" 99e2.5 ", false},
    {"53.5e93", true},
    {" --6 ", false},
    {"-+3", false},
    {"95a54e53", false},

    {"123", true},
    {" 123 ", true},
    {"0", true},
    {"0123", true},
    {"00", true},
    {"-10", true},
    {"-0", true},
    {"123.5", true},
    {"123.000000", true},
    {"-500.777", true},
    {"0.0000001", true},
    {"0.00000", true},
    {"0.", true},
    {"00.5", true},
    {"123e1", true},
    {"1.23e10", true},
    {"0.5e-10", true},
    {"1.0e4.5", false},
    {"0.5e04", true},
    {"12 3", false},
    {"1a3", false},
    {"", false},
    {"     ", false},
    {".1", true},
    {".", false},
    {"2e0", true},
    {"+.8", true},
    {" 005047e+6", true},

    {" c99.7e8 .", false}
};

int main() {
    for (const auto &tc : test_cases) {
        const auto [input, expected] = tc;
        const auto actual = Solution{}.isNumber(input);

        cout << (actual == expected ? "OK  " : "NOK ");
        cout << (actual ? "true " : "false") << " on \"" << input << "\"" << endl;
    }

    return 0;
}
