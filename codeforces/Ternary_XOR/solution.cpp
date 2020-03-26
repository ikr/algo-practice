#include <bits/stdc++.h>

using namespace std;

pair<string, string> summands(const string &x) {
    string a(x.size(), '0');
    string b(x.size(), '0');
    bool favorA = true;
    bool favored = false;

    for (auto i = 0U; i != x.size(); ++i) {
        if (i < x.size() - 1 && x[i] == '1' && x[i + 1] == '2') {
            if (favorA) {
                a[i] = '0';
                a[i + 1] = '2';
                b[i] = '1';
                b[i + 1] = '0';
            } else {
                b[i] = '0';
                b[i + 1] = '2';
                a[i] = '1';
                a[i + 1] = '0';
            }

            if (!favored) {
                favorA = !favorA;
                favored = true;
            }

            ++i;
        } else {
            switch (x[i]) {
            case '1':
                if (favorA) {
                    b[i] = '1';
                } else {
                    a[i] = '1';
                }
                break;

            case '2':
                a[i] = '1';
                b[i] = '1';
                break;
            }
        }
    }

    return {b, a};
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
