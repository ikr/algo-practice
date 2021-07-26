#include <bits/stdc++.h>

using namespace std;

enum class State { EQUAL, A_IS_GREATER };

pair<string, string> summands(const string &x) {
    string a(x.size(), '0');
    string b(x.size(), '0');
    State s = State::EQUAL;

    for (auto i = 0U; i != x.size(); ++i) {
        switch (s) {
        case State::EQUAL:
            if (x[i] == '1') {
                a[i] = '1';
                s = State::A_IS_GREATER;
            } else if (x[i] == '2') {
                a[i] = '1';
                b[i] = '1';
            }
            break;

        case State::A_IS_GREATER:
            if (x[i] == '1') {
                b[i] = '1';
            } else if (x[i] == '2') {
                b[i] = '2';
            }
            break;
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
