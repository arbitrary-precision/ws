#include "../common.hpp"

TEST(asm_cmp, build)
{
    AP_REGISTER(l, 1, 1, false, 1);
    AP_REGISTER(r, 1, 1, false, 1);
    asm_cmp(rregister(l), rregister(r));
}

// Name: [outcome] [where unequality occurs] [left trimmed] [right trimmed]
// Outcome is (l)ess, (g)reater, (e)qual.
// Unequality occurs (n)owhere (equal), (e)nd, (m)iddle, (b)egin.
TEST(asm_cmp, entt)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 4, 5);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 4, 5);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::equal);
    ASSERT_EQ(result.size, 0);
}

TEST(asm_cmp, lett)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 4, 4);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 4, 5);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::less);
    ASSERT_EQ(result.size, 5);
}

TEST(asm_cmp, lmtt)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 2, 4, 5);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 4, 5);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::less);
    ASSERT_EQ(result.size, 3);
}

TEST(asm_cmp, lbtt)
{
    AP_REGISTER(l, 5, 5, false, 0, 2, 3, 4, 5);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 4, 5);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::less);
    ASSERT_EQ(result.size, 1);
}

TEST(asm_cmp, gett)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 4, 5);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 4, 4);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::greater);
    ASSERT_EQ(result.size, 5);
}

TEST(asm_cmp, gmtt)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 4, 5);
    AP_REGISTER(r, 5, 5, false, 1, 2, 2, 4, 5);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::greater);
    ASSERT_EQ(result.size, 3);
}

TEST(asm_cmp, gbtt)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 4, 5);
    AP_REGISTER(r, 5, 5, false, 0, 2, 3, 4, 5);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::greater);
    ASSERT_EQ(result.size, 1);
}

TEST(asm_cmp, enuu)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 4, 0);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 4, 0);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::equal);
    ASSERT_EQ(result.size, 0);
}

TEST(asm_cmp, leuu)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 4, 0);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 4, 5);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::less);
    ASSERT_EQ(result.size, 5);
}

TEST(asm_cmp, lmuu)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 2, 0, 0);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 0, 0);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::less);
    ASSERT_EQ(result.size, 3);
}

TEST(asm_cmp, lbuu)
{
    AP_REGISTER(l, 5, 5, false, 0, 2, 3, 0, 0);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 0, 0);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::less);
    ASSERT_EQ(result.size, 1);
}

TEST(asm_cmp, geuu)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 4, 5);
    AP_REGISTER(r, 5, 5, false, 1, 2, 3, 4, 0);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::greater);
    ASSERT_EQ(result.size, 5);
}

TEST(asm_cmp, gmuu)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 0, 0);
    AP_REGISTER(r, 5, 5, false, 1, 2, 2, 0, 0);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::greater);
    ASSERT_EQ(result.size, 3);
}

TEST(asm_cmp, gbuu)
{
    AP_REGISTER(l, 5, 5, false, 1, 2, 3, 0, 0);
    AP_REGISTER(r, 5, 5, false, 0, 2, 3, 0, 0);
    cmpres result = asm_cmp(rregister(l), rregister(r));
    ASSERT_EQ(result.result, cmpres::greater);
    ASSERT_EQ(result.size, 1);
}
