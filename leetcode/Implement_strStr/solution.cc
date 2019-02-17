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
    int strStr(const string &hst, const string &ndl) {
        if (ndl.size() == 0)
            return 0;

        if (hst.size() < ndl.size())
            return -1;

        if (hst.size() == ndl.size())
            return hst == ndl ? 0 : -1;

        const vector<int> lps = build_lps(ndl);
        int i = 0;
        int j = 0;
        while (i <= hst.size() - ndl.size()) {
            while (j < ndl.size() && hst[i + j] == ndl[j])
                ++j;

            if (j == ndl.size())
                return i;

            ++i;

            if (j > 0) {
                j = lps[j - 1];
            } else {
                j = 0;
            }
        }

        return -1;
    }

  private:
    static vector<int> build_lps(const string &s) {
        const int sz = s.size();
        vector<int> lps(sz);

        for (int l = 1; l <= sz; ++l) {
            lps[l - 1] = max_proper_pre_suffix_length(s.substr(0, l));
        }

        return lps;
    }

    static int max_proper_pre_suffix_length(const string &s) {
        int result = 0;

        for (int l = 1; l != s.size(); ++l) {
            if (head(s, l) == tail(s, l))
                result = l;
        }

        return result;
    }

    static string head(const string &s, int l) { return s.substr(0, l); }

    static string tail(const string &s, int l) {
        return s.substr(s.size() - l, l);
    }
};

class RKSolution {
  public:
    int strStr(const string &haystack, const string &needle) { return -1; }
};

ostream &operator<<(ostream &os, const vector<int> &v) {
    for (auto x : v) {
        os << x << ' ';
    }

    return os;
}

int main() {
    KMPSolution s;

    cout << s.strStr("hello", "ll") << endl;
    cout << s.strStr("aaaaa", "bba") << endl;
    cout << s.strStr("bacbababababcabcbab", "abababca") << endl;
    cout << s.strStr("AAABAAAABA", "AAAA") << endl;

    cout << s.strStr("bbbbbbbaababbbaaaabbbbaabaaaababaababaaabababaababbbbbbaa"
                     "baaaabbaabaab"
                     "abbbbabbabbbaaaaaabaaaaabbaabbbbaaaaaabababaaaaa",
                     "babbbbaababababbabaaaaabaabaaaabab")
         << endl;

    return 0;
}
