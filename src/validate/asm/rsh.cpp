#include "../common.hpp"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(asm_rsh, build)
{
    AP_REGISTER(l, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(o, 1, 1, false, AP_WCHESS1);
    asm_rsh(rregister(l), 1, o);
}

// Macro call structure:
// name,
//         ls      l4          l3          l2          l1
//         rs      r4          r3          r2          r1
//         es      e4          e3          e2          e1
// name  - [left size] [left trimmed]
// l/r/e - left/right/expected
// xs    - size
// x4    - the most significant word
// x1    - the least significant word
#define AP_TEST_RSH(n, ls, l4, l3, l2, l1, es, e4, e3, e2, e1) \
    TEST(asm_rsh, n)                                           \
    {                                                          \
        AP_REGISTER(l, 4, ls, false, l1, l2, l3, l4);          \
        AP_REGISTER(o, 4, 0, false);                           \
        AP_REGISTER(e, 4, es, false, e1, e2, e3, e4);          \
        asm_rsh(rregister(l), word_traits::bits / 2, o);       \
        AP_ASSERT_REG(o, e);                                   \
    }

AP_TEST_RSH(ot,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYHW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW);

AP_TEST_RSH(ou,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);

AP_TEST_RSH(ht,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYHW);

AP_TEST_RSH(hu,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED);

AP_TEST_RSH(ft,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            4, AP_WZEROED, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW);

AP_TEST_RSH(fu,
            4, AP_WZEROED, AP_WFILLED, AP_WONLYLW, AP_WFILLED,
            4, AP_WZEROED, AP_WONLYLW, AP_WONLYHW, AP_WFILLED);
