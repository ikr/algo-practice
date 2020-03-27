#include <bits/stdc++.h>

using namespace std;

enum class State { INITIAL, JUST_SAW_ONE, AFTER_ONE_TWO };

pair<string, string> summands(const string &x) {
    string a(x.size(), '0');
    string b(x.size(), '0');
    State s = State::INITIAL;

    for (auto i = 0U; i != x.size(); ++i) {
        switch (s) {
        case State::INITIAL:
            if (x[i] == '1') {
                a[i] = '1';
                s = State::JUST_SAW_ONE;
            } else if (x[i] == '2') {
                a[i] = '1';
                b[i] = '1';
            }
            break;

        case State::JUST_SAW_ONE:
            if (x[i] == '1') {
                a[i] = '1';
            } else if (x[i] == '2') {
                a[i] = '0';
                b[i] = '2';
                s = State::AFTER_ONE_TWO;
            }
            break;

        case State::AFTER_ONE_TWO:
            if (x[i] == '1') {
                b[i] = '1';
            } else if (x[i] == '2') {
                a[i] = '1';
                b[i] = '1';
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
