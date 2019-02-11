#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

class KMPSolution {
  public:
    int strStr(const string &haystack, const string &needle) { return -1; }
};

class RKSolution {
  public:
    int strStr(const string &haystack, const string &needle) { return -1; }
};

int main() {
    KMPSolution s;

    cout << s.strStr("hello", "ll") << endl;
    cout << s.strStr("aaaaa", "bba") << endl;
    cout << s.strStr("bacbababababcabcbab", "abababca") << endl;

    return 0;
}
