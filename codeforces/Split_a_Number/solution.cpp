#include <bits/stdc++.h>

using namespace std;

bool digits_less(const string &a, const string &b) {
    if (a.size() == b.size()) return a < b;
    return a.size() < b.size();
}

string add(const string &a, const string &b) {
    auto ia = a.rbegin();
    auto ib = b.rbegin();
    bool carry = false;

    string result;

    while (ia != a.rend() || ib != b.rend()) {
        int d = carry ? 1 : 0;

        if (ia != a.rend() && ib != b.rend()) {
            d += *ia - '0' + *ib - '0';
            ++ia;
            ++ib;
        } else if (ia != a.rend()) {
            d += *ia - '0';
            ++ia;
        } else { // ib != b.rend()
            d += *ib - '0';
            ++ib;
        }

        result += static_cast<char>('0' + (d % 10));
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

    size_t b_start = 1;
    while (digits[b_start] == '0') ++b_start;

    string a = digits.substr(0, b_start);
    string b = digits.substr(b_start, string::npos);
    string result = add(a, b);

    for (b_start = b_start + 1; b_start <= digits.size() - 1; ++b_start) {
        a += digits[b_start - 1];
        b.erase(b.begin(), b.begin() + 1);
        if (digits[b_start] == '0') continue;

        const string the_sum = add(a, b);

        if (digits_less(the_sum, result)) result = the_sum;
    }

    cout << result << '\n';
}
