#include "../common.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(core, tb_fregister)
{
    fregister a{};
    fregister b{a};
    fregister c{std::move(a)};
    fregister d;
    d = b;
    fregister f;
    f = std::move(c);
    index_t i = index_t(f);
    f = f | d;
    f = f & d;
    f = f ^ d;
    f |= d;
    f &= d;
    f ^= d;
    f = ~f;
    bool x = (f == d);
    x = (f != d);
    f.flip(d);
    f.set(d);
    f.unset(d);
    x = f.has_any(d);
    x = f.has_all(d);
    f.clear();
    x = f.empty();
    ASSERT_EQ(fregister::noneflag, 0);
    ASSERT_EQ(fregister::infinity, 1);
    ASSERT_EQ(fregister::overflow, 2);
    ASSERT_EQ(fregister::wrapping, 4);
    ASSERT_EQ(fregister::signflip, 8);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unit.

TEST(core, tu_fregister_ctor_default)
{
    fregister flags{};
    ASSERT_EQ(index_t(flags), fregister::noneflag);
}

TEST(core, tu_fregister_ctor_params)
{
    fregister flags{fregister::infinity};
    ASSERT_EQ(index_t(flags), fregister::infinity);
}

TEST(core, tu_fregister_ctor_copy)
{
    fregister flags{fregister::infinity};
    fregister oflags{flags};
    ASSERT_EQ(index_t(oflags), fregister::infinity);
}

TEST(core, tu_fregister_op_assign_copy)
{
    fregister flags{fregister::infinity};
    fregister oflags;
    oflags = flags;
    ASSERT_EQ(index_t(oflags), fregister::infinity);
}

TEST(core, tu_fregister_ctor_move)
{
    fregister flags{fregister::infinity};
    fregister oflags{std::move(flags)};
    ASSERT_EQ(index_t(oflags), fregister::infinity);
}

TEST(core, tu_fregister_op_assign_move)
{
    fregister flags{fregister::infinity};
    fregister oflags;
    oflags = std::move(flags);
    ASSERT_EQ(index_t(oflags), fregister::infinity);
}

TEST(core, tu_fregister_op_index_t)
{
    fregister flags{fregister::infinity};
    ASSERT_EQ(index_t(flags), fregister::infinity);
}

TEST(core, tu_fregister_op_or)
{
    fregister flags{fregister::overflow};
    fregister oflags{fregister::signflip};
    ASSERT_EQ(index_t(flags| oflags), fregister::signflip | fregister::overflow);
}

TEST(core, tu_fregister_op_and)
{
    fregister flags{fregister::signflip | fregister::overflow};
    fregister oflags{fregister::signflip};
    ASSERT_EQ(index_t(flags & oflags), fregister::signflip);
}

TEST(core, tu_fregister_op_xor)
{
    fregister flags{fregister::signflip | fregister::overflow};
    fregister oflags{fregister::signflip};
    ASSERT_EQ(index_t(flags ^ oflags), fregister::overflow);
}

TEST(core, tu_fregister_op_or_assign)
{
    fregister flags{fregister::overflow};
    fregister oflags{fregister::signflip};
    flags |= oflags;
    ASSERT_EQ(index_t(flags), fregister::signflip | fregister::overflow);
}

TEST(core, tu_fregister_op_and_assign)
{
    fregister flags{fregister::signflip | fregister::overflow};
    fregister oflags{fregister::signflip};
    flags &= oflags;
    ASSERT_EQ(index_t(flags), fregister::signflip);
}

TEST(core, tu_fregister_op_xor_assign)
{
    fregister flags{fregister::signflip | fregister::overflow};
    fregister oflags{fregister::signflip};
    flags ^= oflags;
    ASSERT_EQ(index_t(flags), fregister::overflow);
}

TEST(core, tu_fregister_op_not)
{
    fregister flags{fregister::overflow};
    flags = ~flags;
    ASSERT_EQ(index_t(flags), ~index_t{fregister::overflow});
}

TEST(core, tu_fregister_op_eq)
{
    fregister flags{fregister::overflow};
    fregister oflags{fregister::overflow};
    ASSERT_TRUE(flags == oflags);
    oflags = fregister::wrapping;
    ASSERT_FALSE(flags == oflags);
}

TEST(core, tu_fregister_op_ne)
{
    fregister flags{fregister::wrapping};
    fregister oflags{fregister::overflow};
    ASSERT_TRUE(flags != oflags);
    flags = fregister::overflow;
    ASSERT_FALSE(flags != oflags);
}

TEST(core, tu_fregister_flip)
{
    fregister flags{fregister::wrapping | fregister::infinity};
    fregister oflags{fregister::wrapping};
    flags.flip(oflags);
    ASSERT_EQ(index_t(flags), fregister::infinity);
    flags.flip(oflags);
    ASSERT_EQ(index_t(flags), fregister::infinity | fregister::wrapping);
}

TEST(core, tu_fregister_set)
{
    fregister flags{};
    flags.set(fregister::wrapping);
    ASSERT_EQ(index_t(flags), fregister::wrapping);
}

TEST(core, tu_fregister_unset)
{
    fregister flags{fregister::wrapping | fregister::infinity};
    flags.unset(fregister::wrapping);
    ASSERT_EQ(index_t(flags), fregister::infinity);
}

TEST(core, tu_fregister_has_any)
{
    fregister flags{fregister::wrapping | fregister::infinity};
    ASSERT_TRUE(flags.has_any(fregister::wrapping));
    ASSERT_TRUE(flags.has_any(fregister::wrapping | fregister::signflip));
    ASSERT_FALSE(flags.has_any(fregister::signflip));
}

TEST(core, tu_fregister_has_all)
{
    fregister flags{fregister::wrapping | fregister::infinity};
    ASSERT_TRUE(flags.has_all(fregister::wrapping));
    ASSERT_TRUE(flags.has_all(fregister::wrapping | fregister::infinity));
    ASSERT_FALSE(flags.has_all(fregister::wrapping | fregister::signflip));
}

TEST(core, tu_fregister_clear)
{
    fregister flags{fregister::wrapping | fregister::infinity};
    flags.clear();
    ASSERT_EQ(index_t(flags), fregister::noneflag);
}

TEST(core, tu_fregister_empty)
{
    fregister flags{fregister::wrapping | fregister::infinity};
    ASSERT_FALSE(flags.empty());
    flags.clear();
    ASSERT_TRUE(flags.empty());
}
