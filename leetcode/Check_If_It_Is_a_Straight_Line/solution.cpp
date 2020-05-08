using vi = vector<int>;
using Coef = tuple<int, int, int>;

// (y1 - y2) * x + (x1 - x2) * y + (x1 * y2 - x2 * y1) = 0; 

Coef line_equation(const vi &xy1, const vi &xy2) {
    const int x1 = xy1[0];
    const int y1 = xy1[1];
    const int x2 = xy2[0];
    const int y2 = xy2[1];
    
    return {y1 - y2, x2 - x1, x1 * y2 - x2 * y1};
}

bool is_on_line(const Coef &coef, const vi &xy) {
    const auto [A, B, C] = coef;
    const int x = xy[0];
    const int y = xy[1];
    
    return A * x + B * y + C == 0;
}

struct Solution final {
    bool checkStraightLine(const vector<vi> &xys) {
        const auto coef = line_equation(xys[0], xys[1]);
        
        return all_of(
            xys.cbegin() + 2, 
            xys.cend(), 
            [&coef](const auto &xy) { return is_on_line(coef, xy); }
        );
    }
};
