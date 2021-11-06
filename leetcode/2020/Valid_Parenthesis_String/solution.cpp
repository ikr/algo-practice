#include <bits/stdc++.h>

using namespace std;

struct Solution final {
    bool checkValidString(const string &s) const {
        int balance_lo = 0;
        int balance_hi = 0;
        
        for (const auto c : s) {
            switch (c) {
                case '(':
                    ++balance_lo;
                    ++balance_hi;
                    break;

                case ')':
                    balance_lo = max(0, balance_lo - 1);
                    --balance_hi;
                    break;

                case '*':
                    balance_lo = max(0, balance_lo - 1);
                    ++balance_hi;
                    break;
            }
            
            if (balance_hi < 0) return false;
        }
        
        return balance_lo == 0;
    }
};

int main() {
    assert(Solution{}.checkValidString("()"));
    assert(Solution{}.checkValidString("(*)"));
    assert(Solution{}.checkValidString("(*))"));
    assert(Solution{}.checkValidString(""));
    assert(!Solution{}.checkValidString("(*()())))"));
    assert(Solution{}.checkValidString("(*()()))"));
    assert(!Solution{}.checkValidString(")()"));
    assert(!Solution{}.checkValidString("()(*("));
    assert(Solution{}.checkValidString("(**(**)**)"));
    
    return 0;
}
