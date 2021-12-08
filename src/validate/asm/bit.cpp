#include "../common.hpp"

TEST(asm_and, build)
{
    AP_REGISTER(l, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(r, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(o, 1, 1, false, AP_WCHESS1);
    asm_and(rregister(l), rregister(r), o);
}

// Macro call structure:
// name, op, opf,
//         ls      l4          l3          l2          l1
//         rs      r4          r3          r2          r1
//         es      e4          e3          e2          e1
// name   - [left size] [left trimmed] _ [right size] [right trimmed]
// op     - operation symbol (&, |, ^).
// opf    - operation function name (and, or, xor).
// l/r/e  - left/right/expected
// xs     - size
// x4     - the most significant word
// x1     - the least significant word
#define AP_TEST_BIT(n, op, opf, ls, l4, l3, l2, l1, rs, r4, r3, r2, r1) \
    TEST(asm_##opf, n)                                                  \
    {                                                                   \
        word_t e1 = l1 op(rs > 0 ? r1 : AP_WZEROED);                    \
        word_t e2 = l2 op(rs > 1 ? r2 : AP_WZEROED);                    \
        word_t e3 = l3 op(rs > 2 ? r3 : AP_WZEROED);                    \
        word_t e4 = l4 op(rs > 3 ? r4 : AP_WZEROED);                    \
        AP_REGISTER(l, 4, ls, false, l1, l2, l3, l4);                   \
        AP_REGISTER(r, 4, rs, false, r1, r2, r3, r4);                   \
        AP_REGISTER(e, 4, ls, false, e1, e2, e3, e4);                   \
        AP_REGISTER(o, 4, 0, false);                                    \
        asm_##opf(rregister(l), rregister(r), o);                       \
        AP_ASSERT_REG(o, e);                                            \
    }

// Test suite, op - operator as-is, opf - asm function name (without asm_).
#define AP_TEST_BIT_SUITE(op, opf)                                  \
                                                                    \
    AP_TEST_BIT(zt_zt, op, opf,                                     \
                0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,  \
                0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT); \
                                                                    \
    AP_TEST_BIT(ot_zt, op, opf,                                     \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0,  \
                0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT); \
                                                                    \
    AP_TEST_BIT(ou_zt, op, opf,                                     \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,  \
                0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT); \
                                                                    \
    AP_TEST_BIT(ot_ot, op, opf,                                     \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0,  \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED); \
                                                                    \
    AP_TEST_BIT(ou_ot, op, opf,                                     \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,  \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1); \
                                                                    \
    AP_TEST_BIT(ot_ou, op, opf,                                     \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0,  \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED); \
                                                                    \
    AP_TEST_BIT(ou_ou, op, opf,                                     \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,  \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED); \
                                                                    \
    AP_TEST_BIT(ht_zt, op, opf,                                     \
                2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WCHESS0,  \
                0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT); \
                                                                    \
    AP_TEST_BIT(hu_zt, op, opf,                                     \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,  \
                0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT); \
                                                                    \
    AP_TEST_BIT(ht_ot, op, opf,                                     \
                2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WCHESS0,  \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1); \
                                                                    \
    AP_TEST_BIT(hu_ot, op, opf,                                     \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,  \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1); \
                                                                    \
    AP_TEST_BIT(ht_ou, op, opf,                                     \
                2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WCHESS0,  \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED); \
                                                                    \
    AP_TEST_BIT(hu_ou, op, opf,                                     \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,  \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED); \
                                                                    \
    AP_TEST_BIT(ht_ht, op, opf,                                     \
                2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WCHESS0,  \
                2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WFILLED); \
                                                                    \
    AP_TEST_BIT(hu_ht, op, opf,                                     \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,  \
                2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WFILLED); \
                                                                    \
    AP_TEST_BIT(ht_hu, op, opf,                                     \
                2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0,  \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED); \
                                                                    \
    AP_TEST_BIT(hu_hu, op, opf,                                     \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,  \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED); \
                                                                    \
    AP_TEST_BIT(ft_zt, op, opf,                                     \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,  \
                0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT); \
                                                                    \
    AP_TEST_BIT(fu_zt, op, opf,                                     \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,  \
                0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT); \
                                                                    \
    AP_TEST_BIT(ft_ot, op, opf,                                     \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,  \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1); \
                                                                    \
    AP_TEST_BIT(fu_ot, op, opf,                                     \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,  \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1); \
                                                                    \
    AP_TEST_BIT(ft_ou, op, opf,                                     \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,  \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED); \
                                                                    \
    AP_TEST_BIT(fu_ou, op, opf,                                     \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,  \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED); \
                                                                    \
    AP_TEST_BIT(ft_ht, op, opf,                                     \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,  \
                2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WCHESS1); \
                                                                    \
    AP_TEST_BIT(fu_ht, op, opf,                                     \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,  \
                2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WCHESS1); \
                                                                    \
    AP_TEST_BIT(ft_hu, op, opf,                                     \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,  \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1); \
                                                                    \
    AP_TEST_BIT(fu_hu, op, opf,                                     \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,  \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1); \
                                                                    \
    AP_TEST_BIT(ft_ft, op, opf,                                     \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,  \
                4, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1); \
                                                                    \
    AP_TEST_BIT(fu_ft, op, opf,                                     \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,  \
                4, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1); \
                                                                    \
    AP_TEST_BIT(ft_fu, op, opf,                                     \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,  \
                4, AP_WZEROED, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1); \
                                                                    \
    AP_TEST_BIT(fu_fu, op, opf,                                     \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,  \
                4, AP_WZEROED, AP_WZEROED, AP_WCHESS1, AP_WCHESS1);

AP_TEST_BIT_SUITE(&, and)
AP_TEST_BIT_SUITE(|, or)
AP_TEST_BIT_SUITE(^, xor)
