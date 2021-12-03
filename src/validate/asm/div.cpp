#include "../common.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(asm, tb_div)
{
    AP_REGISTER(l, 2, 2, false, 1, 1);
    AP_REGISTER(r, 2, 2, false, 1, 1);
    AP_REGISTER(q, 2, 2, false, AP_WHEPROT, AP_WHEPROT);
    AP_REGISTER(m, 2, 2, false, AP_WHEPROT, AP_WHEPROT);
    asm_div(rregister(l), rregister(r), q, m);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unit.

#define AP_TEST_DIV(p, ls, l4, l3, l2, l1, rs, r4, r3, r2, r1, qs, q4, q3, q2, q1, ms, m4, m3, m2, m1)   \
    TEST(asm, tu_div_##p)                                                      \
    {                                                                                \
        AP_REGISTER(l, 4, ls, false, l1, l2, l3, l4);                                \
        AP_REGISTER(r, 4, rs, false, r1, r2, r3, r4);                                \
        AP_REGISTER(q, 4, 0, false, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT); \
        AP_REGISTER(m, 4, 0, false, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT); \
        AP_REGISTER(eq, 4, qs, false, q1, q2, q3, q4);                               \
        AP_REGISTER(em, 4, ms, false, m1, m2, m3, m4);                               \
        asm_div(rregister(l), rregister(r), q, m);                           \
        AP_ASSERT_REG(q, eq);                                                        \
        AP_ASSERT_REG(m, em);                                                        \
    }

// Macro call structure:
// prefix,
//         ls      l4          l3          l2          l1
//         qs      q4          q3          q2          q1
//         rs      r4          r3          r2          r1
// l/q/r - left/expected quotient/expected remainder
// s - size
// x4 - the most significant word
// x1 - the least significant word

#define AP_DIVISOR word_t(AP_WONLYLW + 1)

AP_TEST_DIV(hhttgq,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYHW, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_DIVISOR, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED);

AP_TEST_DIV(hhtteq,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLB,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED);

AP_TEST_DIV(hhttgr,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYHW, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_DIVISOR, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0);

AP_TEST_DIV(hhttlr,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0);

AP_TEST_DIV(fhttgq,
            4, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYHW, AP_WONLYHW,
            3, AP_WHEPROT, AP_WONLYLB, AP_WZEROED, AP_WONLYLB,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED);

AP_TEST_DIV(fhttgr,
            4, AP_WONLYHW, AP_WONLYHW, AP_WFILLED, AP_WONLYHW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYHW, AP_WONLYHW,
            3, AP_WHEPROT, AP_WONLYLB, AP_WZEROED, AP_WONLYLB,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WZEROED);

AP_TEST_DIV(ffttgq,
            4, AP_WONLYHW, AP_WZEROED, AP_WONLYHW, AP_WZEROED,
            4, AP_DIVISOR, AP_WZEROED, AP_DIVISOR, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            4, AP_WZEROED, AP_WZEROED, AP_WZEROED, AP_WZEROED);

AP_TEST_DIV(fftteq,
            4, AP_WONLYHW, AP_WZEROED, AP_WONLYHW, AP_WZEROED,
            4, AP_WONLYHW, AP_WZEROED, AP_WONLYHW, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLB,
            4, AP_WZEROED, AP_WZEROED, AP_WZEROED, AP_WZEROED);

AP_TEST_DIV(ffttgr,
            4, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW, AP_WZEROED,
            4, AP_DIVISOR, AP_WZEROED, AP_WZEROED, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            4, AP_WZEROED, AP_WONLYHW, AP_WONLYHW, AP_WZEROED);

AP_TEST_DIV(ffttlr,
            4, AP_WONLYLW, AP_WONLYHW, AP_WONLYHW, AP_WZEROED,
            4, AP_DIVISOR, AP_WZEROED, AP_WZEROED, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            4, AP_WONLYLW, AP_WONLYHW, AP_WONLYHW, AP_WZEROED);
