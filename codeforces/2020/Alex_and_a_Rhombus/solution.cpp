#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;

    int result = 0;

    for (int i = 1; i <= n * 2 - 1; ++i) {
        result += (i % 2 ? n : n - 1);
    }

    cout << result << '\n';
}
