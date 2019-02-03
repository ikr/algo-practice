#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <iterator>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
  public:
    bool isValid(string s) {
        const unordered_map<char, char> opener_by_closer{
            {')', '('}, {'}', '{'}, {']', '['}};

        stack<char> memo;

        for (auto c : s) {
            switch (c) {
            case '(':
            case '{':
            case '[':
                memo.push(c);
                break;

            case ')':
            case '}':
            case ']':
                if (memo.empty() || memo.top() != opener_by_closer.at(c)) {
                    return false;
                } else {
                    memo.pop();
                }
            }
        }

        return memo.empty();
    }
};

int main() {
    Solution s;
    string sample = "()(){{}[]";

    cout << sample << endl;
    cout << s.isValid(sample) << endl;

    return 0;
}
