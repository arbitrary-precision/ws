#include "../common.hpp"

TEST(asm_mul_short, build)
{
    AP_REGISTER(l, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(r, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(o, 1, 1, false, AP_WCHESS1);
    asm_mul_short(rregister(l), 1, o);
}

// Macro call structure:
// name, expected carry
//         ls      l4          l3          l2          l1
//         rs      r4          r3          r2          r1
//         es      e4          e3          e2          e1
// name  - [left size] [left trimmed/carry/wrapping] [out size] [out trimmed/carry/wrapping]. carry/wrapping implies trimmed.
// l/r/e - left/right/expected. Right is an out here, since its digits are used in computation.
// s     - size
// x4    - the most significant word
// x1    - the least significant word
#define AP_TEST_MUL(n, ecarry, ls, l4, l3, l2, l1, rs, r4, r3, r2, r1, es, e4, e3, e2, e1) \
    TEST(asm_mul_short, n)                                                                 \
    {                                                                                      \
        AP_REGISTER(l, 4, ls, false, l1, l2, l3, l4);                                      \
        AP_REGISTER(o, 4, rs, false, r1, r2, r3, r4);                                      \
        AP_REGISTER(e, 4, es, false, e1, e2, e3, e4);                                      \
        dword_t c = asm_mul_short(rregister(l), AP_WONLYLW + 1, o);                        \
        AP_ASSERT_REG(o, e);                                                               \
        ASSERT_EQ(c, ecarry);                                                              \
    }

AP_TEST_MUL(ztzt, 0,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);

AP_TEST_MUL(otzt, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYHW);

AP_TEST_MUL(ouzt, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED);

AP_TEST_MUL(otot, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED);

AP_TEST_MUL(otou, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYHW);

AP_TEST_MUL(ouot, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED);

AP_TEST_MUL(ouou, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WZEROED);

AP_TEST_MUL(ococ, 0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WFILLED);

AP_TEST_MUL(htzt, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            3, AP_WHEPROT, AP_WZEROED, AP_WONLYHW, AP_WONLYHW);

AP_TEST_MUL(huzt, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            3, AP_WHEPROT, AP_WZEROED, AP_WZEROED, AP_WONLYHW);

AP_TEST_MUL(htot, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            3, AP_WHEPROT, AP_WZEROED, AP_WONLYHW, AP_WFILLED);

AP_TEST_MUL(htou, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            3, AP_WHEPROT, AP_WZEROED, AP_WONLYHW, AP_WONLYHW);

AP_TEST_MUL(huot, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            3, AP_WHEPROT, AP_WZEROED, AP_WZEROED, AP_WFILLED);

AP_TEST_MUL(huou, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            3, AP_WHEPROT, AP_WZEROED, AP_WZEROED, AP_WONLYHW);

AP_TEST_MUL(hcoc, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            3, AP_WHEPROT, AP_WONLYLW, AP_WFILLED, AP_WFILLED);

AP_TEST_MUL(htht, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW,
            3, AP_WHEPROT, AP_WZEROED, AP_WFILLED, AP_WFILLED);

AP_TEST_MUL(hthu, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            3, AP_WHEPROT, AP_WZEROED, AP_WONLYHW, AP_WFILLED);

AP_TEST_MUL(huht, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW,
            3, AP_WHEPROT, AP_WZEROED, AP_WONLYLW, AP_WFILLED);

AP_TEST_MUL(huhu, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            3, AP_WHEPROT, AP_WZEROED, AP_WZEROED, AP_WFILLED);

AP_TEST_MUL(hchc, 0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            3, AP_WHEPROT, AP_WZEROED, AP_WZEROED, AP_WFILLED);

AP_TEST_MUL(ftzt, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            4, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW);

AP_TEST_MUL(fuzt, 0,
            4, AP_WZEROED, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            4, AP_WZEROED, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW);

AP_TEST_MUL(ftot, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            4, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW, AP_WFILLED);

AP_TEST_MUL(ftou, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            4, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW);

AP_TEST_MUL(fuot, 0,
            4, AP_WZEROED, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            4, AP_WZEROED, AP_WONLYHW, AP_WONLYHW, AP_WFILLED);

AP_TEST_MUL(fuou, 0,
            4, AP_WZEROED, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            4, AP_WZEROED, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW);

AP_TEST_MUL(fcoc, 0,
            4, AP_WONLYLW, AP_WFILLED, AP_WONLYLW, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            4, AP_WFILLED, AP_WONLYHW, AP_WFILLED, AP_WFILLED);

AP_TEST_MUL(fwow, AP_WONLYLW,
            4, AP_WFILLED, AP_WFILLED, AP_WONLYLW, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW,
            4, AP_WFILLED, AP_WONLYHW, AP_WFILLED, AP_WFILLED);

AP_TEST_MUL(ftht, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW,
            4, AP_WONLYHW, AP_WONLYHW, AP_WFILLED, AP_WFILLED);

AP_TEST_MUL(fthu, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            4, AP_WONLYHW, AP_WONLYHW, AP_WONLYHW, AP_WFILLED);

AP_TEST_MUL(fuht, 0,
            4, AP_WZEROED, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW,
            4, AP_WZEROED, AP_WONLYHW, AP_WFILLED, AP_WFILLED);

AP_TEST_MUL(fuhu, 0,
            4, AP_WZEROED, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLW,
            4, AP_WZEROED, AP_WONLYHW, AP_WONLYHW, AP_WFILLED);

AP_TEST_MUL(fchc, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW,
            4, AP_WONLYHW, AP_WONLYHW, AP_WFILLED, AP_WFILLED);

AP_TEST_MUL(fwhw, AP_WONLYLW,
            4, AP_WONLYHW, AP_WFILLED, AP_WONLYLW, AP_WONLYLW,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLW, AP_WONLYLW,
            4, AP_WONLYLW, AP_WONLYHW, AP_WFILLED, AP_WFILLED);

AP_TEST_MUL(ftft, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED);

AP_TEST_MUL(ftfu, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            4, AP_WZEROED, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            4, AP_WONLYHW, AP_WFILLED, AP_WFILLED, AP_WFILLED);

AP_TEST_MUL(fuft, 0,
            4, AP_WZEROED, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            4, AP_WONLYLW, AP_WFILLED, AP_WFILLED, AP_WFILLED);

AP_TEST_MUL(fufu, 0,
            4, AP_WZEROED, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            4, AP_WZEROED, AP_WONLYLW, AP_WONLYLW, AP_WONLYLW,
            4, AP_WZEROED, AP_WFILLED, AP_WFILLED, AP_WFILLED);

AP_TEST_MUL(fcfc, 0,
            4, AP_WONLYLW, AP_WONLYLW, AP_WONLYHW, AP_WONLYLW,
            4, AP_WONLYLW, AP_WZEROED, AP_WONLYLW, AP_WONLYLW,
            4, AP_WFILLED, AP_WFILLED, AP_WONLYLW, AP_WFILLED);

AP_TEST_MUL(fwfw, AP_WONLYLW,
            4, AP_WONLYHW, AP_WONLYLW, AP_WONLYHW, AP_WONLYLW,
            4, AP_WONLYLW, AP_WZEROED, AP_WONLYLW, AP_WONLYLW,
            4, AP_WONLYLW, AP_WFILLED, AP_WONLYLW, AP_WFILLED);
