#include <bits/stdc++.h>

using namespace std;

struct Solution {
    string countAndSay(int n) const;

  private:
    static string next(const string &xs);
};

string Solution::countAndSay(int n) const {
    string result;

    while (n) {
        result = next(result);
        --n;
    }

    return result;
}

string Solution::next(const string &xs) {
    if (xs.empty())
        return "1";

    char x = xs[0];
    int xlength = 1;
    string result;

    for (size_t i = 1; i != xs.size(); ++i) {
        const char y = xs[i];

        if (y == x) {
            ++xlength;
            continue;
        }

        result += to_string(xlength);
        result += x;

        xlength = 1;
        x = y;
    }

    result += to_string(xlength);
    result += x;

    return result;
}

int main() {
    cout << Solution().countAndSay(20) << endl;

    return 0;
}
