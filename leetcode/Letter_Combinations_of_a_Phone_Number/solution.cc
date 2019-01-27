#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  public:
    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) {
            return vector<string>();
        }

        first_combination_in_place(digits.end(), digits.begin());
        vector<string> result{digits};

        while (increment_in_place(digits.rend(), digits.rbegin())) {
            result.push_back(digits);
        }

        return result;
    }

  private:
    static bool increment_in_place(string::const_reverse_iterator rend,
                                   string::reverse_iterator r) {
        bool carry = true;

        while (carry && r != rend) {
            if (next(*r) == -1) {
                *r = opening_by_char.at(*r);
            } else {
                *r = next(*r);
                carry = false;
            }

            r++;
        }

        return !(carry && r == rend);
    }

    static void first_combination_in_place(string::const_iterator end,
                                           string::iterator i) {
        while (i != end) {
            *i = next(*i);
            i++;
        }
    }

    static char next(char x) {
        if (increments_by_char.count(x) == 0) {
            return -1;
        }

        return increments_by_char.at(x);
    }

    static const unordered_map<char, char> increments_by_char;
    static const unordered_map<char, char> opening_by_char;
};

const unordered_map<char, char> Solution::increments_by_char{
    {'2', 'a'}, {'a', 'b'}, {'b', 'c'},

    {'3', 'd'}, {'d', 'e'}, {'e', 'f'},

    {'4', 'g'}, {'g', 'h'}, {'h', 'i'},

    {'5', 'j'}, {'j', 'k'}, {'k', 'l'},

    {'6', 'm'}, {'m', 'n'}, {'n', 'o'},

    {'7', 'p'}, {'p', 'q'}, {'q', 'r'}, {'r', 's'},

    {'8', 't'}, {'t', 'u'}, {'u', 'v'},

    {'9', 'w'}, {'w', 'x'}, {'x', 'y'}, {'y', 'z'}};

const unordered_map<char, char> Solution::opening_by_char{
    {'c', 'a'}, {'f', 'd'}, {'i', 'g'}, {'l', 'j'},
    {'o', 'm'}, {'s', 'p'}, {'v', 't'}, {'z', 'w'}};

int main() {
    Solution s;
    vector<string> result = s.letterCombinations("23");

    for (auto s : result) {
        cout << s << endl;
    }

    return 0;
}
