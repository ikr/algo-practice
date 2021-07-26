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

string result_bound(const string &digits) {
    const size_t sz = digits.size();

    size_t b_start = sz / 2;
    while (digits[b_start] == '0') ++b_start;

    if (b_start == sz) {
        b_start = sz / 2;
        while (digits[b_start] == '0') --b_start;
    }

    string a = digits.substr(0, b_start);
    string b = digits.substr(b_start, string::npos);
    return digits_add(a, b);
}

int main() {
    int length;
    string digits;
    cin >> length >> digits;

    const size_t sz = digits.size();
    string result = result_bound(digits);

    for (size_t b_start = 1; b_start <= sz - 1; ++b_start) {
        if (digits[b_start] == '0' ||
            max(b_start, sz - b_start) > result.size())
            continue;

        const string a = digits.substr(0, b_start);
        const string b = digits.substr(b_start, string::npos);
        const string the_sum = digits_add(a, b);
        if (digits_less(the_sum, result)) result = the_sum;
    }

    cout << result << '\n';
}
