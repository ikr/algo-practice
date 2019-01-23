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
    vector<string> letterCombinations(string digits) {}

    static void increment(string::reverse_iterator r) { bool carry = false; }

    static string::reverse_iterator rightmost_non_final(string &s) {
        string::reverse_iterator result = s.rbegin();

        while (result != s.rend()) {
            if (!is_closing(*result)) {
                return result;
            }

            result++;
        }
    }

    static string first_combination(const string &digits) {
        string result = digits;

        for (char &d : result) {
            d = next(d);
        }

        return result;
    }

    static char next(char x) {
        if (increments_by_char.count(x) == 0) {
            return -1;
        }

        return increments_by_char.at(x);
    }

    static bool is_closing(char x) { return next(x) == -1; }

  private:
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
    string combination = Solution::first_combination("234");

    cout << *Solution::rightmost_non_final(combination);
    cout << endl;

    return 0;
}
