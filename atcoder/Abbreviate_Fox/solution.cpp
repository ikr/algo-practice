#include <bits/stdc++.h>
using namespace std;

pair<int, int> inflate(const string &s, const int l, const int r) {
    const int n = s.size();

    if (l - 1 >= 0 && s[l - 1] == 'f' && r + 2 < n && s[r + 1] == 'o' &&
        s[r + 2] == 'x') {
        return inflate(s, l - 1, r + 2);
    }

    if (l - 2 >= 0 && s[l - 2] == 'f' && s[l - 1] == 'o' && r + 1 < n &&
        s[r + 1] == 'x') {
        return inflate(s, l - 2, r + 1);
    }

    return {l, r};
}

int min_length(string &s) {
    auto i = s.find("fox");

    while (i != string::npos) {
        const auto [l, r] = inflate(s, i, i + 2);
        const int to_remove = r - l + 1;
        s.erase(l, to_remove);
        i = s.find("fox", l);
    }

    return s.size();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;
    string s(n, ' ');
    cin >> s;

    cout << min_length(s) << '\n';
    return 0;
}
