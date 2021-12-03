#include "../common.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(asm, tb_dregister)
{
    wregister a{};
    wregister b{a};
    wregister c{std::move(a)};
    wregister d;
    d = b;
    wregister f;
    f = std::move(c);
    rregister i = rregister(f);
    word_t arr[1];
    f.words = arr;
    bool x = f.has_msb();
    f.clear_msb();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unit.

TEST(core, tu_dregister_ctor_default)
{
    wregister reg{};
    ASSERT_EQ(reg.words, nullptr);
    ASSERT_EQ(reg.capacity, 0);
    ASSERT_EQ(reg.size, 0);
    ASSERT_EQ(reg.sign, 0);
}

TEST(core, tu_dregister_ctor_params)
{
    word_t arr[5];
    wregister reg{&arr[0], 5, 1, true};
    ASSERT_EQ(reg.words, &arr[0]);
    ASSERT_EQ(reg.capacity, 5);
    ASSERT_EQ(reg.size, 1);
    ASSERT_EQ(reg.sign, 1);
}

TEST(core, tu_dregister_ctor_copy)
{
    word_t arr[5];
    wregister oreg{&arr[0], 5, 1, true};
    wregister reg{oreg};
    ASSERT_EQ(reg.words, &arr[0]);
    ASSERT_EQ(reg.capacity, 5);
    ASSERT_EQ(reg.size, 1);
    ASSERT_EQ(reg.sign, 1);
}

TEST(core, tu_dregister_op_copy_assign)
{
    word_t arr[5];
    wregister oreg{&arr[0], 5, 1, true};
    wregister reg;
    reg = oreg;
    ASSERT_EQ(reg.words, &arr[0]);
    ASSERT_EQ(reg.capacity, 5);
    ASSERT_EQ(reg.size, 1);
    ASSERT_EQ(reg.sign, 1);
}

TEST(core, tu_dregister_ctor_move)
{
    word_t arr[5];
    wregister oreg{&arr[0], 5, 1, true};
    wregister reg{std::move(oreg)};
    ASSERT_EQ(reg.words, &arr[0]);
    ASSERT_EQ(reg.capacity, 5);
    ASSERT_EQ(reg.size, 1);
    ASSERT_EQ(reg.sign, 1);
}

TEST(core, tu_dregister_op_move_assign)
{
    word_t arr[5];
    wregister oreg{&arr[0], 5, 1, true};
    wregister reg;
    reg = std::move(oreg);
    ASSERT_EQ(reg.words, &arr[0]);
    ASSERT_EQ(reg.capacity, 5);
    ASSERT_EQ(reg.size, 1);
    ASSERT_EQ(reg.sign, 1);
}

TEST(core, tu_dregister_op_dregister_const_word)
{
    word_t arr[5];
    wregister oreg{&arr[0], 5, 1, true};
    rregister reg = rregister(oreg);
    ASSERT_EQ(reg.words, &arr[0]);
    ASSERT_EQ(reg.capacity, 5);
    ASSERT_EQ(reg.size, 1);
    ASSERT_EQ(reg.sign, 1);
}

TEST(core, tu_dregister_has_msb_nomsb_short)
{
    word_t arr[5] = {1, 2, 3, 4, word_traits::ones};
    wregister oreg{&arr[0], 5, 4, true};
    ASSERT_FALSE(oreg.has_msb());
}

TEST(core, tu_dregister_has_msb_nomsb_full)
{
    word_t arr[5] = {1, 2, 3, 4, 5};
    wregister oreg{&arr[0], 5, 5, true};
    ASSERT_FALSE(oreg.has_msb());
}

TEST(core, tu_dregister_has_msb_with_msb)
{
    word_t arr[5] = {1, 2, 3, 4, word_traits::ones};
    wregister oreg{&arr[0], 5, 5, true};
    ASSERT_TRUE(oreg.has_msb());
}

TEST(core, tu_dregister_clear_msb)
{
    word_t arr[5] = {1, 2, 3, 4, word_traits::ones};
    wregister oreg{&arr[0], 5, 5, true};
    oreg.clear_msb();
    ASSERT_EQ(oreg.words[4], word_traits::ones >> 1);
}
