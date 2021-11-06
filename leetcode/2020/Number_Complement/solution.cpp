using ui = unsigned int;

struct Solution final {
    int findComplement(const int x) const {
        const ui sz = sizeof(int) * CHAR_BIT;
        const ui ux = static_cast<ui>(x);
        if ((1U << (sz - 1U)) & ux) return ~ux;
        
        const ui lz = __builtin_clz(x);        
        const ui mask = (1U << (sz - lz)) - 1U;
        
        return ~ux & mask;
    }
};
