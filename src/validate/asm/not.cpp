#include "../common.hpp"

TEST(asm_not, build)
{
    AP_REGISTER(i, 4, 0, false);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    asm_not(rregister(i), o);
}

// Name: [in size] [in trimmed]

TEST(asm_not, zt)
{
    AP_REGISTER(i, 4, 0, false);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED);
    asm_not(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm_not, ot)
{
    AP_REGISTER(i, 4, 1, false, AP_WONLYLB);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, AP_WMISSLB, AP_WFILLED, AP_WFILLED, AP_WFILLED);
    asm_not(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm_not, ht)
{
    AP_REGISTER(i, 4, 2, false, AP_WONLYLB, AP_WONLYLB);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, AP_WMISSLB, AP_WMISSLB, AP_WFILLED, AP_WFILLED);
    asm_not(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm_not, ft)
{
    AP_REGISTER(i, 4, 4, false, AP_WFILLED, AP_WFILLED, AP_WFILLED, AP_WFILLED);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, AP_WZEROED, AP_WZEROED, AP_WZEROED, AP_WZEROED);
    asm_not(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm_not, ou)
{
    AP_REGISTER(i, 4, 4, false, AP_WONLYLB, AP_WZEROED, AP_WZEROED, AP_WZEROED);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, AP_WMISSLB, AP_WFILLED, AP_WFILLED, AP_WFILLED);
    asm_not(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm_not, hu)
{
    AP_REGISTER(i, 4, 4, false, AP_WONLYLB, AP_WONLYLB, AP_WZEROED, AP_WZEROED);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, AP_WMISSLB, AP_WMISSLB, AP_WFILLED, AP_WFILLED);
    asm_not(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm_not, fu)
{
    AP_REGISTER(i, 4, 4, false, AP_WFILLED, AP_WFILLED, AP_WZEROED, AP_WZEROED);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, AP_WZEROED, AP_WZEROED, AP_WFILLED, AP_WFILLED);
    asm_not(rregister(i), o);
    AP_ASSERT_REG(o, e);
}
