string play_backspaces(string s) {
    int i = s.size() - 1;
    int to_delete = 0;
    
    while (i >= 0) {
        if (s[i] == '#') {
            ++to_delete;
            s.erase(i, 1);
            --i;
        } else {
            if (to_delete) {
                s.erase(i, 1);
                --i;
                --to_delete;
            } else {
                --i;
            }
        }
    }
    
    return s;
}

class Solution {
public:
    bool backspaceCompare(string S, string T) {
        return play_backspaces(S) == play_backspaces(T);
    }
};
