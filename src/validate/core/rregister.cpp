#include <gtest/gtest.h>
#include <ap/core.hpp>

using namespace ap::library;

TEST(core, t_rregister_constructor_default)
{
    rregister a;
    ASSERT_EQ(a.words, nullptr);
    ASSERT_EQ(a.capacity, 0);
    ASSERT_EQ(a.size, 0);
    ASSERT_EQ(a.sign, 0);
}

TEST(core, t_rregister_constructor_parameters)
{
    word_t arr[5];
    rregister a{&arr[0], 5, 1, true};
    ASSERT_EQ(a.words, &arr[0]);
    ASSERT_EQ(a.capacity, 5);
    ASSERT_EQ(a.size, 1);
    ASSERT_EQ(a.sign, 1);
}

TEST(core, t_rregister_constructor_copy)
{
    word_t arr[5];
    rregister b{&arr[0], 5, 1, true};
    rregister a{b};
    ASSERT_EQ(a.words, &arr[0]);
    ASSERT_EQ(a.capacity, 5);
    ASSERT_EQ(a.size, 1);
    ASSERT_EQ(a.sign, 1);
}

TEST(core, t_rregister_operator_copy_assignment)
{
    word_t arr[5];
    rregister b{&arr[0], 5, 1, true};
    rregister a;
    a = b;
    ASSERT_EQ(a.words, &arr[0]);
    ASSERT_EQ(a.capacity, 5);
    ASSERT_EQ(a.size, 1);
    ASSERT_EQ(a.sign, 1);
}

TEST(core, t_rregister_constructor_move)
{
    word_t arr[5];
    rregister b{&arr[0], 5, 1, true};
    rregister a{std::move(b)};
    ASSERT_EQ(a.words, &arr[0]);
    ASSERT_EQ(a.capacity, 5);
    ASSERT_EQ(a.size, 1);
    ASSERT_EQ(a.sign, 1);
}

TEST(core, t_rregister_operator_move_assignment)
{
    word_t arr[5];
    rregister b{&arr[0], 5, 1, true};
    rregister a;
    a = std::move(b);
    ASSERT_EQ(a.words, &arr[0]);
    ASSERT_EQ(a.capacity, 5);
    ASSERT_EQ(a.size, 1);
    ASSERT_EQ(a.sign, 1);
}

TEST(core, t_rregister_operator_dregister_const_word)
{
    word_t arr[5];
    rregister b{&arr[0], 5, 1, true};
    auto a = static_cast<rregister>(b);
    ASSERT_EQ(a.words, &arr[0]);
    ASSERT_EQ(a.capacity, 5);
    ASSERT_EQ(a.size, 1);
    ASSERT_EQ(a.sign, 1);
}

TEST(core, t_rregister_has_msb_nomsb_short)
{
    word_t arr[5] = {1, 2, 3, 4, word_traits::ones};
    rregister b{&arr[0], 5, 4, true};
    ASSERT_FALSE(b.has_msb());
}

TEST(core, t_rregister_has_msb_nomsb_full)
{
    word_t arr[5] = {1, 2, 3, 4, 5};
    rregister b{&arr[0], 5, 5, true};
    ASSERT_FALSE(b.has_msb());
}

TEST(core, t_rregister_has_msb_msb)
{
    word_t arr[5] = {1, 2, 3, 4, word_traits::ones};
    rregister b{&arr[0], 5, 5, true};
    ASSERT_TRUE(b.has_msb());
}
