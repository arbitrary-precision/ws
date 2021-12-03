#include "../common.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(asm, tb_sub)
{
    AP_REGISTER(l, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(r, 1, 1, false, AP_WONLYLB);
    AP_REGISTER(o, 1, 1, false, AP_WCHESS1);
    asm_sub(rregister(l), rregister(r), o);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unit.

#define AP_TEST_SUB(p, ls, l4, l3, l2, l1, rs, r4, r3, r2, r1, es, e4, e3, e2, e1) \
    TEST(asm, tu_sub_##p)                                                          \
    {                                                                              \
        AP_REGISTER(l, 4, ls, false, l1, l2, l3, l4);                              \
        AP_REGISTER(r, 4, rs, false, r1, r2, r3, r4);                              \
        AP_REGISTER(o, 4, 0, false);                                               \
        AP_REGISTER(e, 4, es, false, e1, e2, e3, e4);                              \
        asm_sub(rregister(l), rregister(r), o);                                    \
        AP_ASSERT_REG(o, e);                                                       \
    }

// Macro call structure:
// prefix,
//         ls      l4          l3          l2          l1
//         rs      r4          r3          r2          r1
//         es      e4          e3          e2          e1
// l/r/e - left/right/expected
// s - size
// x4 - the most significant word
// x1 - the least significant word

AP_TEST_SUB(oztt,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED);

AP_TEST_SUB(oott,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1);

AP_TEST_SUB(ootu,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED);

AP_TEST_SUB(hztt,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED);

AP_TEST_SUB(hzut,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED);

AP_TEST_SUB(hott,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WCHESS1);

AP_TEST_SUB(hotu,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED);

AP_TEST_SUB(hout,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1);

AP_TEST_SUB(houu,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED);

AP_TEST_SUB(hhtt,
            2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WCHESS1);

AP_TEST_SUB(hhtu,
            2, AP_WHEPROT, AP_WHEPROT, AP_WONLYLB, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WONLYLB,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED);

AP_TEST_SUB(hhuu,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1);

AP_TEST_SUB(fztt,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED);

AP_TEST_SUB(fzut,
            4, AP_WZEROED, AP_WZEROED, AP_WZEROED, AP_WFILLED,
            0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,
            4, AP_WZEROED, AP_WZEROED, AP_WZEROED, AP_WFILLED);

AP_TEST_SUB(fott,
            4, AP_WFILLED, AP_WFILLED, AP_WONLYLB, AP_WZEROED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WONLYLB,
            4, AP_WFILLED, AP_WFILLED, AP_WZEROED, AP_WFILLED);

AP_TEST_SUB(fotu,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED);

AP_TEST_SUB(fout,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WCHESS1);

AP_TEST_SUB(fouu,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WFILLED,
            1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WFILLED);

AP_TEST_SUB(fhtt,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0,
            4, AP_WFILLED, AP_WFILLED, AP_WCHESS1, AP_WCHESS1);

AP_TEST_SUB(fhtu,
            4, AP_WFILLED, AP_WFILLED, AP_WONLYLB, AP_WZEROED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            4, AP_WFILLED, AP_WFILLED, AP_WZEROED, AP_WONLYLB);

AP_TEST_SUB(fhut,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0,
            4, AP_WZEROED, AP_WZEROED, AP_WCHESS1, AP_WCHESS1);

AP_TEST_SUB(fhuu,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WFILLED,
            2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WZEROED);

AP_TEST_SUB(fftt,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            4, AP_WFILLED, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            4, AP_WZEROED, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);

AP_TEST_SUB(fftu,
            4, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED,
            4, AP_WZEROED, AP_WCHESS0, AP_WCHESS0, AP_WCHESS0,
            4, AP_WFILLED, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);

AP_TEST_SUB(ffuu,
            4, AP_WZEROED, AP_WONLYLB, AP_WZEROED, AP_WFILLED,
            4, AP_WZEROED, AP_WZEROED, AP_WONLYLB, AP_WZEROED,
            4, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WFILLED);
