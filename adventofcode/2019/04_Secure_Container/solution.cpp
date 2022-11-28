#include <bits/stdc++.h>
using namespace std;

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

int potential_passwords_count(const int A, const int B) {
    cerr << "A:" << A << " B:" << B << endl;
    return -1;
}

int main() {
    string line;
    cin >> line;

    const auto parts = split("-", line);
    const auto A = stoi(parts[0]);
    const auto B = stoi(parts[1]);

    cout << potential_passwords_count(A, B) << '\n';
    return 0;
}
