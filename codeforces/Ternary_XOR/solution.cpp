#include <bits/stdc++.h>

using namespace std;

pair<string, string> summands(const string &x) {
    string a(x.size(), '0');
    string b(x.size(), '0');
    bool saw_one = false;

    for (auto i = 0U; i != x.size(); ++i) {
        if (saw_one) {
            if (x[i] == '2') {
                b[i] = '2';
            } else if (x[i] == '1'){
                b[i] = '1';
            }

            continue;
        }

        if (x[i] == '1') {
            a[i] = '1';
            saw_one = true;
        } else if (x[i] == '2') {
            a[i] = '1';
            b[i] = '1';
        }
    }

    return {a, b};
}

int main() {
    int t;
    cin >> t;

    for (int i = 0; i != t; ++i) {
        int n;
        cin >> n;
        string x(n, '0');
        cin >> x;

        assert(x[0] == '2');

        const auto [a, b] = summands(x);
        cout << a << '\n' << b << '\n';
    }

    return 0;
}
