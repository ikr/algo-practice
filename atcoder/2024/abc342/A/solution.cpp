#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    string xs;
    cin >> xs;

    map<char, int> fq;
    for (const auto x : xs) ++fq[x];

    char c = ' ';
    for (const auto [k, v] : fq) {
        if (v == 1) {
            c = k;
            break;
        }
    }
    assert(c != ' ');

    cout << (find(cbegin(xs), cend(xs), c) - cbegin(xs)) + 1 << '\n';
    return 0;
}
