#include <bits/stdc++.h>
using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

int query(const int l, const int r) {
    cout << "? " << l << ' ' << r << endl;
    int x;
    cin >> x;
    return x;
}

void print_answer(const vector<int> &xs) {
    cout << "! " << xs.size();
    if (!xs.empty()) cout << ' ' << xs;
    cout << endl;
}

void interact(const int n) {
    vector<int> pref(n + 2, 0);
    vector<int> suff(n + 2, 0);

    for (int i = 1; i <= n; ++i) {
        pref[i] = query(1, i);
        suff[i] = query(i, n);
    }

    vector<int> xs;
    xs.reserve(n / 2);

    for (int i = 1; i <= n; ++i) {
        if (pref[i] == pref[i - 1] + 1 && suff[i] == suff[i + 1] + 1) {
            xs.push_back(i);
        }
    }

    print_answer(xs);
}

int main() {
    int n;
    cin >> n;
    interact(n);
    return 0;
}
