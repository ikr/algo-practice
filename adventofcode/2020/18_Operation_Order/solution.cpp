#include <bits/stdc++.h>
using namespace std;

int main() {
    for (string line; getline(cin, line);) {
        line.erase(remove(begin(line), end(line), ' '), cend(line));
        cout << line << '\n';
    }
    return 0;
}
