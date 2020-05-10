string print_tail(const int max_width, const vector<string> &line, const int line_width) {
    string buf;
    
    for (auto i = 0U; i != line.size(); ++i) {
        if (i) buf += ' ';
        buf += line[i];
    }    
    
    const string suffix(max_width - line_width, ' ');
    return buf + suffix;
}

string print_line(const int max_width, const vector<string> &line, const int line_width) {
    if (line.size() == 1) return print_tail(max_width, line, line_width);
    
    const int spaces_count = line.size() - 1;
    const int budget = max_width - line_width;
    const int ideal_step = budget / spaces_count;
    const int padding = budget % spaces_count;
    
    string ans;
    for (auto i = 0U; i != line.size(); ++i) {
        if (i) {
            ans += string(ideal_step + 1, ' ');
            if (padding && i <= padding) ans += ' ';
        }
        
        ans += line[i];
    }
    
    return ans;
}

struct Solution final {
    vector<string> fullJustify(const vector<string> &ss, const int max_width) const {
        vector<string> ans;
        vector<string> line;
        int line_width = 0;
        
        for (const auto &s : ss) {
            const int nlw = line_width ? line_width + 1 + s.size() : s.size(); 
            
            if (nlw == max_width) {
                line.push_back(s);
                ans.push_back(print_line(max_width, line, nlw));
                line.resize(0);
                line_width = 0;
            } else if (nlw > max_width) {
                ans.push_back(print_line(max_width, line, line_width));
                line = vector<string>{s};
                line_width = s.size();
            } else {
                line.push_back(s);
                line_width = nlw;
            }
        }
        
        if (line_width > 0) ans.push_back(print_tail(max_width, line, line_width));
        return ans;
    }
};
