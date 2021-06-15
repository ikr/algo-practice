#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

vector<string::size_type> all_positions(const string &s, const string &t) {
    vector<string::size_type> ans;

    for (string::size_type i = 0; i != string::npos;) {
        i = s.find(t, i);

        if (i != string::npos) {
            ans.push_back(i + 1);
            ++i;
        }
    }

    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    int n;
    cin >> n;
    while (n--) {
        string s, t;
        cin >> s >> t;
        cout << all_positions(s, t) << '\n';
    }

    return 0;
}
