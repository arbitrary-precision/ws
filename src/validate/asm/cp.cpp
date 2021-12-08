#include "../common.hpp"

TEST(asm_cp, build)
{
    AP_REGISTER(i, 1, 1, false, 1);
    AP_REGISTER(o, 1, 1, false, 1);
    asm_cp(rregister(i), o);
}

// Name - [in size] [in trimmed]

TEST(asm_cp, zt)
{
    AP_REGISTER(i, 4, 0, false, 1);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 0, false, 0);
    asm_cp(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm_cp, ot)
{
    AP_REGISTER(i, 4, 1, false, 1);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 1, false, 1);
    asm_cp(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm_cp, ht)
{
    AP_REGISTER(i, 4, 2, false, 1, 2);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 2, false, 1, 2);
    asm_cp(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm_cp, ft)
{
    AP_REGISTER(i, 4, 4, false, 1, 2, 3, 4);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, 1, 2, 3, 4);
    asm_cp(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm_cp, uo)
{
    AP_REGISTER(i, 4, 1, false, 0);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 1, false, 0);
    asm_cp(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm_cp, hu)
{
    AP_REGISTER(i, 4, 2, false, 1, 0);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 2, false, 1, 0);
    asm_cp(rregister(i), o);
    AP_ASSERT_REG(o, e);
}

TEST(asm_cp, fu)
{
    AP_REGISTER(i, 4, 4, false, 1, 2, 0, 0);
    AP_REGISTER(o, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    AP_REGISTER(e, 4, 4, false, 1, 2, 0, 0);
    asm_cp(rregister(i), o);
    AP_ASSERT_REG(o, e);
}
