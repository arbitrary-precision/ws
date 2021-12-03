#include "../common.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(asm, tb_cmp)
{
    AP_REGISTER(l, 1, 1, false, 1);
    AP_REGISTER(r, 1, 1, false, 1);
    asm_cmp(rregister(l), rregister(r));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unit.

// tu_cmp_OTW
// O - outcome, less (l), greater (g), equal (e)
// T - trimmed (t) or untrimmed (u)
// W - where unequal, begin (b), middle (m), end (e), none (n)

TEST(asm, tu_cmp_entt)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 4, 5);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 4, 5);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::equal);
    ASSERT_EQ(result.size, 0);
}

TEST(asm, tu_cmp_lett)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 4, 4);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 4, 5);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::less);
    ASSERT_EQ(result.size, 5);
}

TEST(asm, tu_cmp_lmtt)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 2, 4, 5);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 4, 5);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::less);
    ASSERT_EQ(result.size, 3);
}

TEST(asm, tu_cmp_lbtt)
{
    AP_REGISTER(l, 5, 5, false, 0, 2, 3, 4, 5);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 4, 5);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::less);
    ASSERT_EQ(result.size, 1);
}

TEST(asm, tu_cmp_gett)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 4, 5);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 4, 4);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::greater);
    ASSERT_EQ(result.size, 5);
}

TEST(asm, tu_cmp_gmtt)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 4, 5);
    AP_REGISTER(r, 5, 5, false, 1, 2, 2, 4, 5);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::greater);
    ASSERT_EQ(result.size, 3);
}

TEST(asm, tu_cmp_gbtt)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 4, 5);
    AP_REGISTER(r, 5, 5, false, 0, 2, 3, 4, 5);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::greater);
    ASSERT_EQ(result.size, 1);
}

TEST(asm, tu_cmp_enuu)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 4, 0);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 4, 0);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::equal);
    ASSERT_EQ(result.size, 0);
}

TEST(asm, tu_cmp_leuu)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 4, 0);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 4, 5);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::less);
    ASSERT_EQ(result.size, 5);
}

TEST(asm, tu_cmp_lmuu)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 2, 0, 0);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 0, 0);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::less);
    ASSERT_EQ(result.size, 3);
}

TEST(asm, tu_cmp_lbuu)
{
    AP_REGISTER(l, 5, 5, false, 0, 2, 3, 0, 0);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 0, 0);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::less);
    ASSERT_EQ(result.size, 1);
}

TEST(asm, tu_cmp_geuu)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 4, 5);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 4, 0);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::greater);
    ASSERT_EQ(result.size, 5);
}

TEST(asm, tu_cmp_gmuu)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 0, 0);
    AP_REGISTER(r, 5, 5, false, 1, 2, 2, 0, 0);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::greater);
    ASSERT_EQ(result.size, 3);
}

TEST(asm, tu_cmp_gbuu)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 0, 0);
    AP_REGISTER(r, 5, 5, false, 0, 2, 3, 0, 0);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::greater);
    ASSERT_EQ(result.size, 1);
}
