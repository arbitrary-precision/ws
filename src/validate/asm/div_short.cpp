#include "../common.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(asm, tb_div_short)
{
    AP_REGISTER(l, 2, 2, false, 1, 1);
    AP_REGISTER(q, 2, 2, false, AP_WHEPROT, AP_WHEPROT);
    AP_REGISTER(m, 2, 2, false, AP_WHEPROT, AP_WHEPROT);
    asm_div_short(rregister(l), 1, q, m);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unit.

#define AP_TEST_DIV(p, ls, l4, l3, l2, l1, qs, q4, q3, q2, q1, ms, m4, m3, m2, m1)   \
    TEST(asm, tu_div_short_##p)                                                      \
    {                                                                                \
        AP_REGISTER(l, 4, ls, false, l1, l2, l3, l4);                                \
        AP_REGISTER(q, 4, 0, false, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT); \
        AP_REGISTER(m, 4, 0, false, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT); \
        AP_REGISTER(eq, 4, qs, false, q1, q2, q3, q4);                               \
        AP_REGISTER(em, 4, ms, false, m1, m2, m3, m4);                               \
        asm_div_short(rregister(l), AP_WONLYLW + 1, q, m);                           \
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

AP_TEST_DIV(oqt,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYHW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);

AP_TEST_DIV(oqu,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);

AP_TEST_DIV(hqt,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WONLYHW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);

AP_TEST_DIV(hqu,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYHW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);

AP_TEST_DIV(fqt,
            4, AP_WONLYLW, AP_WFILLED, AP_WFILLED, AP_WONLYHW,
            4, AP_WZEROED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);

AP_TEST_DIV(fqu,
            4, AP_WZEROED, AP_WFILLED, AP_WFILLED, AP_WONLYHW,
            4, AP_WZEROED, AP_WONLYLW, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);

AP_TEST_DIV(ort,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW);

AP_TEST_DIV(hrt,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW);

AP_TEST_DIV(hru,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW);

AP_TEST_DIV(frt,
            4, AP_WONLYLW, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            4, AP_WZEROED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW);

AP_TEST_DIV(fru,
            4, AP_WZEROED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            4, AP_WZEROED, AP_WONLYLW, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW);
