#include <gtest/gtest.h>
#include <ap/int_alg.hpp>
#include "../../utils.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(int_alg, tb_uint_tstr)
{
    REGISTER(in, 1, 1, false, 1);
    uint_tstr(rregister(in), 1, "1");
}
