#include <bits/stdc++.h>

using namespace std;

using ull_t = unsigned long long;

int main() {
    ull_t n;
    cin >> n;

    const ull_t result = (n % 2) ? 0 : 2ULL << (n / 2 - 1);
    cout << result << '\n';
}
