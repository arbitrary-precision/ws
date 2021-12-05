#include "../common.hpp"


TEST(asm_trim, build)
{
    AP_REGISTER(x, 1, 1, false, 0);
    asm_trim(x);
}

// Name: [in size] [in trimmed]

TEST(asm_trim, zt)
{
    AP_REGISTER(x, 4, 0, false);
    AP_REGISTER(e, 4, 0, false);
    asm_trim(x);
    AP_ASSERT_REG(x, e);
}

TEST(asm_trim, ot)
{
    AP_REGISTER(x, 4, 1, false, 1);
    AP_REGISTER(e, 4, 1, false, 1);
    asm_trim(x);
    AP_ASSERT_REG(x, e);
}

TEST(asm_trim, ht)
{
    AP_REGISTER(x, 4, 2, false, 1, 2);
    AP_REGISTER(e, 4, 2, false, 1, 2);
    asm_trim(x);
    AP_ASSERT_REG(x, e);
}

TEST(asm_trim, ft)
{
    AP_REGISTER(x, 4, 4, false, 1, 2, 3, 4);
    AP_REGISTER(e, 4, 4, false, 1, 2, 3, 4);
    asm_trim(x);
    AP_ASSERT_REG(x, e);
}

TEST(asm_trim, zu)
{
    AP_REGISTER(x, 4, 4, false, 0, 0, 0, 0);
    AP_REGISTER(e, 4, 0, false);
    asm_trim(x);
    AP_ASSERT_REG(x, e);
}

TEST(asm_trim, ou)
{
    AP_REGISTER(x, 4, 4, false, 1, 0, 0, 0);
    AP_REGISTER(e, 4, 1, false, 1);
    asm_trim(x);
    AP_ASSERT_REG(x, e);
}

TEST(asm_trim, hu)
{
    AP_REGISTER(x, 4, 4, false, 1, 2, 0, 0);
    AP_REGISTER(e, 4, 2, false, 1, 2);
    asm_trim(x);
    AP_ASSERT_REG(x, e);
}
