#include <gtest/gtest.h>
#include <ap/array.hpp>

using namespace ap::library;

TEST(array, t_alloc)
{
    index_t size = 10000;
    array<word_t> arr = array_alloc<word_t>(size);
    for (index_t i = 0; i < size; ++i)
    {
        arr[i] = i;
    }
}

TEST(array, t_realloc)
{
    index_t size = 10000;
    array<word_t> arr = array_alloc<word_t>(size);
    for (index_t i = 0; i < size; ++i)
    {
        arr[i] = i;
    }
    size = 100000;
    array_realloc(arr, size);
    for (index_t i = 0; i < size; ++i)
    {
        arr[i] = i;
    }
}
