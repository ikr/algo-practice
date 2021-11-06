#include <bits/stdc++.h>

using namespace std;

string do_shift(string s, const int offset) {
    if (!offset) return s;
    
    if (offset < 0) {
        string ss(s, 0, -offset);
        s.erase(0, -offset);
        s = s + ss;
    } else {
        string ss(s, s.size() - offset);
        s.erase(s.size() - offset);
        s = ss + s; 
    }
    
    return s;
}

class Solution {
public:
    string stringShift(const string &s, const vector<vector<int>> &shifts) {
        int offset = 0;
        
        for (const auto &shift : shifts) {
            const bool shift_right = shift[0] == 1;
            const int steps = shift[1];
            
            if (shift_right) offset += steps;
            else offset -= steps;
        }
        
        return do_shift(s, offset % static_cast<int>(s.size()));
    }
};

int main() {
    const auto actual = Solution{}.stringShift("wpdhhcj", {{0,7},{1,7},{1,0},{1,3},{0,3},{0,6},{1,2}});
    
    cout << "ACT " << actual << endl;
    cout << "EXP hcjwpdh\n";
    
    return 0;
}
