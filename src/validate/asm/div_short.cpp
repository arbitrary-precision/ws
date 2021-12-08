#include "../common.hpp"

TEST(asm_div_short, build)
{
    AP_REGISTER(l, 2, 2, false, 1, 1);
    AP_REGISTER(q, 2, 2, false, AP_WHEPROT, AP_WHEPROT);
    AP_REGISTER(m, 2, 2, false, AP_WHEPROT, AP_WHEPROT);
    asm_div_short(rregister(l), 1, q, m);
}

// Macro call structure:
// name,
//         ls      l4          l3          l2          l1
//         qs      q4          q3          q2          q1
//         rs      r4          r3          r2          r1
// name  - [left size] [left trimmed] [operation (quotient or remainder)]
// l/q/r - left/expected quotient/expected remainder
// xs    - size
// x4    - the most significant word
// x1    - the least significant word
#define AP_TEST_DIV(n, ls, l4, l3, l2, l1, qs, q4, q3, q2, q1, ms, m4, m3, m2, m1)   \
    TEST(asm_div_short, n)                                                           \
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

AP_TEST_DIV(otq,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYHW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);

AP_TEST_DIV(ouq,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);

AP_TEST_DIV(htq,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WONLYHW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);

AP_TEST_DIV(huq,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYHW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);

AP_TEST_DIV(ftq,
            4, AP_WONLYLW, AP_WFILLED, AP_WFILLED, AP_WONLYHW,
            4, AP_WZEROED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);

AP_TEST_DIV(fuq,
            4, AP_WZEROED, AP_WFILLED, AP_WFILLED, AP_WONLYHW,
            4, AP_WZEROED, AP_WONLYLW, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);

AP_TEST_DIV(otr,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW);

AP_TEST_DIV(htr,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW);

AP_TEST_DIV(hur,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW);

AP_TEST_DIV(ftr,
            4, AP_WONLYLW, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            4, AP_WZEROED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW);

AP_TEST_DIV(fur,
            4, AP_WZEROED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            4, AP_WZEROED, AP_WONLYLW, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW);
