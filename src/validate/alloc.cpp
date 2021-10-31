#include <gtest/gtest.h>
#include <ap/alloc.hpp>

TEST(Build, alloc_alloc) {
    auto ptr = ap::library::alloc<int>(200);
}

TEST(Build, alloc_realloc) {
    auto ptr = ap::library::alloc<int>(1000);
    ap::library::realloc<int>(ptr, 50000);
}
