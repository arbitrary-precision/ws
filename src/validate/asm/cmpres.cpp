#include <gtest/gtest.h>
#include <ap/asm.hpp>

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unit.

TEST(asm, tu_cmpres_constructor_default)
{
    cmpres result{};
    ASSERT_EQ(result.result, cmpres::equal);
    ASSERT_EQ(result.size, 0);
}

TEST(asm, tu_cmpres_constructor_params)
{
    cmpres result{result.greater, 5};
    ASSERT_EQ(result.result, cmpres::greater);
    ASSERT_EQ(result.size, 5);
}
