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
  private:
    static const unordered_map<char, char> increments_by_char;
    static char inc(char x) { return 0; }
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

int main() {
    Solution s;

    cout << '\n';

    return 0;
}
