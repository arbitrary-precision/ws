#include "../common.hpp"

using namespace ap::library;

TEST(core_fregister, build)
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
}

TEST(core_fregister, ctor_d)
{
    fregister flags{};
    ASSERT_EQ(index_t(flags), fregister::noneflag);
}

TEST(core_fregister, ctor_p)
{
    fregister flags{fregister::infinity};
    ASSERT_EQ(index_t(flags), fregister::infinity);
}

TEST(core_fregister, ctor_c)
{
    fregister flags{fregister::infinity};
    fregister oflags{flags};
    ASSERT_EQ(index_t(oflags), fregister::infinity);
}

TEST(core_fregister, op_assign_copy)
{
    fregister flags{fregister::infinity};
    fregister oflags;
    oflags = flags;
    ASSERT_EQ(index_t(oflags), fregister::infinity);
}

TEST(core_fregister, ctor_m)
{
    fregister flags{fregister::infinity};
    fregister oflags{std::move(flags)};
    ASSERT_EQ(index_t(oflags), fregister::infinity);
}

TEST(core_fregister, op_assign_move)
{
    fregister flags{fregister::infinity};
    fregister oflags;
    oflags = std::move(flags);
    ASSERT_EQ(index_t(oflags), fregister::infinity);
}

TEST(core_fregister, op_index_t)
{
    fregister flags{fregister::infinity};
    ASSERT_EQ(index_t(flags), fregister::infinity);
}

TEST(core_fregister, op_or)
{
    fregister flags{fregister::overflow};
    fregister oflags{fregister::infinity};
    ASSERT_EQ(index_t(flags | oflags), fregister::infinity | fregister::overflow);
}

TEST(core_fregister, op_and)
{
    fregister flags{fregister::infinity | fregister::overflow};
    fregister oflags{fregister::infinity};
    ASSERT_EQ(index_t(flags & oflags), fregister::infinity);
}

TEST(core_fregister, op_xor)
{
    fregister flags{fregister::infinity | fregister::overflow};
    fregister oflags{fregister::infinity};
    ASSERT_EQ(index_t(flags ^ oflags), fregister::overflow);
}

TEST(core_fregister, op_or_assign)
{
    fregister flags{fregister::overflow};
    fregister oflags{fregister::infinity};
    flags |= oflags;
    ASSERT_EQ(index_t(flags), fregister::infinity | fregister::overflow);
}

TEST(core_fregister, op_and_assign)
{
    fregister flags{fregister::infinity | fregister::overflow};
    fregister oflags{fregister::infinity};
    flags &= oflags;
    ASSERT_EQ(index_t(flags), fregister::infinity);
}

TEST(core_fregister, op_xor_assign)
{
    fregister flags{fregister::infinity | fregister::overflow};
    fregister oflags{fregister::infinity};
    flags ^= oflags;
    ASSERT_EQ(index_t(flags), fregister::overflow);
}

TEST(core_fregister, op_not)
{
    fregister flags{fregister::overflow};
    flags = ~flags;
    ASSERT_EQ(index_t(flags), ~index_t{fregister::overflow});
}

TEST(core_fregister, op_eq)
{
    fregister flags{fregister::overflow};
    fregister oflags{fregister::overflow};
    ASSERT_TRUE(flags == oflags);
    oflags = fregister::infinity;
    ASSERT_FALSE(flags == oflags);
}

TEST(core_fregister, op_ne)
{
    fregister flags{fregister::infinity};
    fregister oflags{fregister::overflow};
    ASSERT_TRUE(flags != oflags);
    flags = fregister::overflow;
    ASSERT_FALSE(flags != oflags);
}

TEST(core_fregister, flip)
{
    fregister flags{fregister::overflow | fregister::infinity};
    fregister oflags{fregister::overflow};
    flags.flip(oflags);
    ASSERT_EQ(index_t(flags), fregister::infinity);
    flags.flip(oflags);
    ASSERT_EQ(index_t(flags), fregister::infinity | fregister::overflow);
}

TEST(core_fregister, set)
{
    fregister flags{};
    flags.set(fregister::overflow);
    ASSERT_EQ(index_t(flags), fregister::overflow);
}

TEST(core_fregister, unset)
{
    fregister flags{fregister::overflow | fregister::infinity};
    flags.unset(fregister::overflow);
    ASSERT_EQ(index_t(flags), fregister::infinity);
}

TEST(core_fregister, has_any)
{
    fregister flags{fregister::overflow | fregister::infinity};
    ASSERT_TRUE(flags.has_any(fregister::overflow));
    ASSERT_TRUE(flags.has_any(fregister::overflow | fregister::infinity));
}

TEST(core_fregister, has_all)
{
    fregister flags{fregister::overflow | fregister::infinity};
    ASSERT_TRUE(flags.has_all(fregister::overflow));
    ASSERT_TRUE(flags.has_all(fregister::overflow | fregister::infinity));
}

TEST(core_fregister, clear)
{
    fregister flags{fregister::overflow | fregister::infinity};
    flags.clear();
    ASSERT_EQ(index_t(flags), fregister::noneflag);
}

TEST(core_fregister, empty)
{
    fregister flags{fregister::overflow | fregister::infinity};
    ASSERT_FALSE(flags.empty());
    flags.clear();
    ASSERT_TRUE(flags.empty());
}
