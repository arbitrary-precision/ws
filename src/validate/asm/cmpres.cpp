#include "../common.hpp"

TEST(asm_cmpres, build)
{
    cmpres result{};
}

TEST(asm_cmpres, ctor_d)
{
    cmpres result{};
    ASSERT_EQ(result.result, cmpres::equal);
    ASSERT_EQ(result.size, 0);
}

TEST(asm, ctor_p)
{
    cmpres result{result.greater, 5};
    ASSERT_EQ(result.result, cmpres::greater);
    ASSERT_EQ(result.size, 5);
}
