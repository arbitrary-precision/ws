#include "../common.hpp"

TEST(asm_add, build)
{
    AP_REGISTER(l, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(r, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(o, 1, 1, false, AP_WCHESS1);
    asm_add(rregister(l), rregister(r), o);
}

// Macro call structure:
// name, expected carry
//         ls      l4          l3          l2          l1
//         rs      r4          r3          r2          r1
//         es      e4          e3          e2          e1
// name  - [left size] [left trimmed/carry/wrapping] [right size] [right trimmed/carry/wrapping]. carry/wrapping implies trimmed.
// l/r/e - left/right/expected
// xs    - size
// x4    - the most significant word
// x1    - the least significant word
#define AP_TEST_ADD(n, ecarry, ls, l4, l3, l2, l1, rs, r4, r3, r2, r1, es, e4, e3, e2, e1) \
    TEST(asm_add, n)                                                                       \
    {                                                                                      \
        AP_REGISTER(l, 4, ls, false, l1, l2, l3, l4);                                      \
        AP_REGISTER(r, 4, rs, false, r1, r2, r3, r4);                                      \
        AP_REGISTER(o, 4, 0, false);                                                       \
        AP_REGISTER(e, 4, es, false, e1, e2, e3, e4);                                      \
        dword_t c = asm_add(rregister(l), rregister(r), o);                                \
        AP_ASSERT_REG(o, e);                                                               \
        ASSERT_EQ(c, ecarry);                                                              \
    }

AP_TEST_ADD(ztzt, 0,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);

AP_TEST_ADD(otzt, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED);

AP_TEST_ADD(ouzt, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED);

AP_TEST_ADD(otot, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED);

AP_TEST_ADD(otou, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0);

AP_TEST_ADD(ouot, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1);

AP_TEST_ADD(ouou, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED);

AP_TEST_ADD(ococ, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLB,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLB, AP_WZEROED);

AP_TEST_ADD(htzt, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            3, AP_WHEPROT, AP_WZEROED, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(huzt, 0,
            2, AP_WHEPROT, AP_WZEROED, AP_WZEROED, AP_WFILLED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            3, AP_WHEPROT, AP_WZEROED, AP_WZEROED, AP_WFILLED);

AP_TEST_ADD(htot, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1,
            3, AP_WHEPROT, AP_WZEROED, AP_WCHESS0, AP_WFILLED);

AP_TEST_ADD(htou, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            3, AP_WHEPROT, AP_WZEROED, AP_WCHESS0, AP_WCHESS0);

AP_TEST_ADD(huot, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1,
            3, AP_WHEPROT, AP_WZEROED, AP_WZEROED, AP_WFILLED);

AP_TEST_ADD(huou, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            3, AP_WHEPROT, AP_WZEROED, AP_WZEROED, AP_WCHESS0);

AP_TEST_ADD(hcoc, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED,
            3, AP_WHEPROT, AP_WONLYLB, AP_WZEROED, AP_WMISSLB);

AP_TEST_ADD(htht, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WCHESS1,
            3, AP_WHEPROT, AP_WZEROED, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(hthu, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1,
            3, AP_WHEPROT, AP_WZEROED, AP_WCHESS0, AP_WFILLED);

AP_TEST_ADD(huht, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WCHESS1,
            3, AP_WHEPROT, AP_WZEROED, AP_WCHESS1, AP_WFILLED);

AP_TEST_ADD(huhu, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1,
            3, AP_WHEPROT, AP_WZEROED, AP_WZEROED, AP_WFILLED);

AP_TEST_ADD(hchc, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WONLYLB,
            3, AP_WHEPROT, AP_WONLYLB, AP_WFILLED, AP_WZEROED);

AP_TEST_ADD(ftzt, 0,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0);

AP_TEST_ADD(fuzt, 0,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0);

AP_TEST_ADD(ftot, 0,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS1);

AP_TEST_ADD(ftou, 0,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0);

AP_TEST_ADD(fuot, 0,
            4, AP_WZEROED, AP_WZEROED, AP_WCHESS0, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1,
            4, AP_WZEROED, AP_WZEROED, AP_WCHESS0, AP_WFILLED);

AP_TEST_ADD(fuou, 0,
            4, AP_WZEROED, AP_WZEROED, AP_WCHESS0, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            4, AP_WZEROED, AP_WZEROED, AP_WCHESS0, AP_WCHESS0);

AP_TEST_ADD(fcoc, 0,
            4, AP_WZEROED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLB,
            4, AP_WONLYLB, AP_WZEROED, AP_WZEROED, AP_WZEROED);

AP_TEST_ADD(fwow, 1,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLB,
            4, AP_WZEROED, AP_WZEROED, AP_WZEROED, AP_WZEROED);

AP_TEST_ADD(ftht, 0,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WCHESS1,
            4, AP_WCHESS0, AP_WCHESS0, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(fthu, 0,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WFILLED);

AP_TEST_ADD(fuht, 0,
            4, AP_WZEROED, AP_WZEROED, AP_WCHESS0, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WCHESS1,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(fuhu, 0,
            4, AP_WZEROED, AP_WZEROED, AP_WCHESS0, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1,
            4, AP_WZEROED, AP_WZEROED, AP_WCHESS0, AP_WFILLED);

AP_TEST_ADD(fchc, 0,
            4, AP_WCHESS0, AP_WZEROED, AP_WONLYLB, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WZEROED,
            4, AP_WCHESS0, AP_WONLYLB, AP_WZEROED, AP_WCHESS0);

AP_TEST_ADD(fwhw, 1,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLB, AP_WCHESS1,
            4, AP_WZEROED, AP_WZEROED, AP_WZEROED, AP_WFILLED);

AP_TEST_ADD(ftft, 0,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            4, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(ftfu, 0,
            4, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            4, AP_WZEROED, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1,
            4, AP_WCHESS0, AP_WFILLED, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(fuft, 0,
            4, AP_WZEROED, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            4, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1,
            4, AP_WCHESS1, AP_WFILLED, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(fufu, 0,
            4, AP_WZEROED, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            4, AP_WZEROED, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1,
            4, AP_WZEROED, AP_WFILLED, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(fcfc, 0,
            4, AP_WZEROED, AP_WONLYLB, AP_WCHESS0, AP_WCHESS0,
            4, AP_WZEROED, AP_WFILLED, AP_WCHESS1, AP_WCHESS1,
            4, AP_WONLYLB, AP_WZEROED, AP_WFILLED, AP_WFILLED);

AP_TEST_ADD(fwfw, 1,
            4, AP_WFILLED, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            4, AP_WONLYLB, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1,
            4, AP_WZEROED, AP_WFILLED, AP_WFILLED, AP_WFILLED);
