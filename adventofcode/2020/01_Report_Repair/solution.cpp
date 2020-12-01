#include <bits/stdc++.h>
using namespace std;

int main() {
    set<int> discovered;

    for (string line; getline(cin, line);) {
        const int x = stoi(line);
        const int to_add = 2020 - x;

        if (discovered.count(to_add)) {
            cout << (x * to_add) << '\n';
            break;
        }

        discovered.insert(x);
    }

    return 0;
}
