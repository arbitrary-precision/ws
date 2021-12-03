#include "../common.hpp"

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(array, tb_array)
{
    array<word_t> arrn = array_null<word_t>();
    array<word_t> arr = array_alloc<word_t>(1);
    array_realloc<word_t>(arr, 2);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unit.

TEST(array, tu_null)
{
    array<word_t> arr = array_null<word_t>();
    ASSERT_TRUE(arr.get() == nullptr);
}

TEST(array, tu_alloc)
{
    index_t size = 127;
    array<word_t> arr = array_alloc<word_t>(size);
    for (index_t i = 0; i < size; ++i)
    {
        arr[i] = i;
        ASSERT_EQ(arr[i], i);
    }
}

TEST(array, tu_realloc)
{
    index_t size = 127;
    array<word_t> arr = array_alloc<word_t>(size);
    for (index_t i = 0; i < size; ++i)
    {
        arr[i] = i;
        ASSERT_EQ(arr[i], i);
    }
    size = 255;
    array_realloc(arr, size);
    for (index_t i = 0; i < size; ++i)
    {
        arr[i] = i;
        ASSERT_EQ(arr[i], i);
    }
}
