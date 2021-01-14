#include <bits/stdc++.h>
using namespace std;

int literal_to_cents(string literal) {
    literal.erase(find(literal.cbegin(), literal.cend(), '.'));
    return stoi(literal);
}

string cents_to_literal(const int x) {
    const string s = to_string(x);
    const int sz = s.size();

    if (sz == 1) return "0.0" + s;
    if (sz == 2) return "0." + s;
    return s.substr(0, sz - 2) + "." + s.substr(sz - 2);
}

int min_movement(const vector<int> &xs) { return 0; }

int main() {
    for (;;) {
        int n;
        cin >> n;
        if (!n) break;

        vector<string> literals(n);
        for (auto &literal : literals) cin >> literal;

        vector<int> xs(n);
        transform(literals.cbegin(), literals.cend(), begin(xs),
                  literal_to_cents);

        cout << ("$" + cents_to_literal(min_movement(xs))) << '\n';
    }

    return 0;
}
