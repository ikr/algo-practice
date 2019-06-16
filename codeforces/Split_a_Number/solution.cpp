#include <bits/stdc++.h>

using namespace std;

string add(const string &a, const string &b) {
    auto ia = a.rbegin();
    auto ib = b.rbegin();
    bool carry = false;

    string result;

    while (ia != a.rend() || ib != b.rend()) {
        int d = 0;

        if (ia != a.rend() && ib != b.rend()) {
            d = *ia - '0' + *ib - '0';
            ++ia;
            ++ib;
        } else if (ia != a.rend()) {
            d = *ia - '0';
            ++ia;
        } else { // ib != b.rend()
            d = *ib - '0';
            ++ib;
        }

        result += static_cast<char>('0' + (d % 10) + (carry ? 1 : 0));
        carry = (d / 10);
    }

    if (carry) result += '1';

    reverse(result.begin(), result.end());
    return result;
}

int main() {
    int length;
    string digits;
    cin >> length >> digits;

    cout << add(digits, digits) << '\n';
}
