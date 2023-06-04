#include <bits/stdc++.h>
using namespace std;

static const vector BasePattern{0, 1, 0, -1};

vector<int> digits(const string &s) {
    vector<int> xs(size(s));
    transform(cbegin(s), cend(s), begin(xs),
              [](const char x) -> int { return x - '0'; });
    return xs;
}

string bignum(const vector<int> &digits) {
    stringstream ss;
    for (const auto d : digits) ss << d;
    return ss.str();
}

constexpr int keep_last_digit(const int x) { return abs(x) % 10; }

vector<int> apply_phase(const vector<int> &pat, const vector<int> &src) {
    return src;
}

int main() {
    string s;
    cin >> s;

    cout << bignum(digits(s)) << '\n';
    return 0;
}
