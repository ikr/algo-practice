#include <bits/stdc++.h>

using namespace std;

bool digits_less(const string &a, const string &b) {
    if (a.size() == b.size()) return a < b;
    return a.size() < b.size();
}

string digits_min(const string &a, const string &b) {
    return digits_less(a, b) ? a : b;
}

string digits_add(const string &a, const string &b) {
    auto ia = a.rbegin();
    auto ib = b.rbegin();
    bool carry = false;

    string result(max(a.size(), b.size()) + 1, '?');
    size_t i = result.size() - 1;

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

        result[i] = static_cast<char>('0' + (d % 10));
        carry = (d / 10);
        --i;
    }

    if (carry)
        result[i] = '1';
    else
        result.erase(result.begin());

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
    string result = digits_add(a, b);

    for (b_start = b_start + 1; b_start <= digits.size() - 1; ++b_start) {
        a += digits[b_start - 1];
        b.erase(b.begin(), b.begin() + 1);

        if (digits[b_start] == '0' || max(a.size(), b.size()) > result.size())
            continue;

        const string the_sum = digits_add(a, b);
        if (digits_less(the_sum, result)) result = the_sum;
    }

    cout << result << '\n';
}
