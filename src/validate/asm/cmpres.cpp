#include "../common.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(asm, tb_cmpres)
{
    cmpres result{};
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unit.

TEST(asm, tu_cmpres_ctor_default)
{
    cmpres result{};
    ASSERT_EQ(result.result, cmpres::equal);
    ASSERT_EQ(result.size, 0);
}

TEST(asm, tu_cmpres_ctor_params)
{
    cmpres result{result.greater, 5};
    ASSERT_EQ(result.result, cmpres::greater);
    ASSERT_EQ(result.size, 5);
}
