#include <bits/stdc++.h>
using namespace std;

int max_occurances(const int k, const string &s) {
    const int n = s.size();
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, k;
    cin >> n >> k;
    string s(n, ' ');
    cin >> s;

    cout << max_occurances(k, s) << '\n';
    return 0;
}
