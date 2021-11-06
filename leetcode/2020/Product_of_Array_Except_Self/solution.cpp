#include <bits/stdc++.h>

using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';

    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }

    os << ']';
    return os;
}

struct Solution final {
    vector<int> productExceptSelf(vector<int>& xs) const {
        vector<int> ans(xs.size(), 1);
        for (auto i = 1U; i != xs.size(); ++i) ans[i] = ans[i - 1] * xs[i - 1];

        int prod = 1;

        for (auto i = xs.size() - 1U; i-- != 0U;) {
            prod *= xs[i + 1];
            ans[i] *= prod;
        }

        return ans;
    }
};

int main() {
    vector<int> input{1,2,3,4};
    const auto actual = Solution{}.productExceptSelf(input);
    const vector<int> expected{24,12,8,6};
    
    cout << "ACT " << actual << endl;
    cout << "EXP " << expected << endl;
    
    assert(actual == expected);
    
    return 0;
}
