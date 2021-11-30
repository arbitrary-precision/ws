#include <gtest/gtest.h>
#include <ap/core.hpp>

using namespace ap::library;

TEST(core, t_fregister_constructor_default)
{
    fregister a;
    ASSERT_EQ(index_t(a), 0);
}

TEST(core, t_fregister_constructor_parameters)
{
    fregister a{10};
    ASSERT_EQ(index_t(a), 10);
}

TEST(core, t_fregister_constructor_copy)
{
    fregister a{11};
    fregister b{a};
    ASSERT_EQ(index_t(b), 11);
}

TEST(core, t_fregister_operator_copy_assignment)
{
    fregister a{12};
    fregister b;
    b = a;
    ASSERT_EQ(index_t(b), 12);
}

TEST(core, t_fregister_constructor_move)
{
    fregister a{13};
    fregister b{std::move(a)};
    ASSERT_EQ(index_t(b), 13);
}

TEST(core, t_fregister_operator_move_assignemnt)
{
    fregister a{14};
    fregister b;
    b = std::move(a);
    ASSERT_EQ(index_t(b), 14);
}

TEST(core, t_fregister_operator_index_t)
{
    fregister a{15};
    ASSERT_EQ(index_t(a), 15);
}

TEST(core, t_fregister_operator_or)
{
    fregister a{16};
    fregister b{32};
    ASSERT_EQ(index_t(a | b), 48);
}

TEST(core, t_fregister_operator_and)
{
    fregister a{48};
    fregister b{32};
    ASSERT_EQ(index_t(a & b), 32);
}

TEST(core, t_fregister_operator_xor)
{
    fregister a{48};
    fregister b{32};
    ASSERT_EQ(index_t(a ^ b), 16);
}

TEST(core, t_fregister_operator_or_assignemnt)
{
    fregister a{16};
    fregister b{32};
    a |= b;
    ASSERT_EQ(index_t(a), 48);
}

TEST(core, t_fregister_operator_and_assignemnt)
{
    fregister a{48};
    fregister b{32};
    a &= b;
    ASSERT_EQ(index_t(a), 32);
}

TEST(core, t_fregister_operator_xor_assignemnt)
{
    fregister a{48};
    fregister b{32};
    a ^= b;
    ASSERT_EQ(index_t(a), 16);
}

TEST(core, t_fregister_operator_not)
{
    fregister a{2};
    a = ~a;
    ASSERT_EQ(index_t(a), ~index_t{2});
}

TEST(core, t_fregister_operator_equal)
{
    fregister a{48};
    fregister b{48};
    ASSERT_TRUE(a == b);
    b = 32;
    ASSERT_FALSE(a == b);
}

TEST(core, t_fregister_operator_not_equal)
{
    fregister a{48};
    fregister b{32};
    ASSERT_TRUE(a != b);
    b = 48;
    ASSERT_FALSE(a != b);
}

TEST(core, t_fregister_flip)
{
    fregister a{48};
    fregister b{48};
    a.flip(b);
    ASSERT_EQ(index_t(a), 0);
    a.flip(b);
    ASSERT_EQ(index_t(a), 48);
}

TEST(core, t_fregister_set)
{
    fregister a{0};
    a.set(48);
    ASSERT_EQ(index_t(a), 48);
}

TEST(core, t_fregister_unset)
{
    fregister a{48};
    a.unset(32);
    ASSERT_EQ(index_t(a), 16);
}

TEST(core, t_fregister_has_any)
{
    fregister a{48};
    ASSERT_TRUE(a.has_any(32));
    ASSERT_FALSE(a.has_any(15));
    ASSERT_TRUE(a.has_any(31));
}

TEST(core, t_fregister_has_all)
{
    fregister a{48};
    ASSERT_TRUE(a.has_all(48));
    ASSERT_TRUE(a.has_all(16));
    ASSERT_FALSE(a.has_all(49));
}

TEST(core, t_fregister_clear)
{
    fregister a{48};
    a.clear();
    ASSERT_EQ(index_t(a), 0);
}

TEST(core, t_fregister_empty)
{
    fregister a{48};
    ASSERT_FALSE(a.empty());
    a.clear();
    ASSERT_TRUE(a.empty());
}
