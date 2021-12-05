#include "../common.hpp"


TEST(asm_fill, build)
{
    AP_REGISTER(x, 1, 1, false, 0);
    asm_fill(x, AP_WCHESS1);
}

// Name: [inout size]

TEST(asm_fill, z)
{
    AP_REGISTER(x, 4, 0, false, 0);
    AP_REGISTER(e, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    asm_fill(x, AP_WCHESS1);
    AP_ASSERT_REG(x, e);
}

TEST(asm_fill, o)
{
    AP_REGISTER(x, 4, 1, false, 1);
    AP_REGISTER(e, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    asm_fill(x, AP_WCHESS1);
    AP_ASSERT_REG(x, e);
}

TEST(asm_fill, h)
{
    AP_REGISTER(x, 4, 2, false, 1, 2);
    AP_REGISTER(e, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    asm_fill(x, AP_WCHESS1);
    AP_ASSERT_REG(x, e);
}

TEST(asm_fill, f)
{
    AP_REGISTER(x, 4, 4, false, 1, 2, 3, 4);
    AP_REGISTER(e, 4, 4, false, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);
    asm_fill(x, AP_WCHESS1);
    AP_ASSERT_REG(x, e);
}
