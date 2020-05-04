using ui = unsigned int;

struct Solution final {
    int bitwiseComplement(const int x) const {
        if (!x) return 1;
        
        const ui sz = sizeof(int) * CHAR_BIT;
        const ui ux = static_cast<ui>(x);
        
        const ui lz = __builtin_clz(x);        
        const ui mask = (1U << (sz - lz)) - 1U;
        
        return ~ux & mask;
    }
};
