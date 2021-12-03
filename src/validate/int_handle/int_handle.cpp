#include "../common.hpp"

using int_handle2 = int_handle<dword_traits::bits, word_traits::bits>;
using int_handle4 = int_handle<dword_traits::bits * 2, word_traits::bits * 2>;
using int_handle8 = int_handle<dword_traits::bits * 4, word_traits::bits * 4>;

#define HANDLE(_type, _name, _capacity, _size, _sign) \
    _type _name{_capacity};                           \
    _name.set_size(_size);                            \
    _name.set_sign(_sign);                            \
    wregister _name##_reg = _name.get_wregister();    \
    for (index_t i = 0; i < _name##_reg.size; ++i)    \
    {                                                 \
        _name##_reg.words[i] = word_t(i);             \
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Build.

TEST(int_handle, tb_int_handle)
{
    ASSERT_EQ(int_handle2::maxbits, word_traits::bits * int_handle2::maxwords);
    ASSERT_EQ(int_handle2::minbits, word_traits::bits * int_handle2::minwords);
    ASSERT_EQ(int_handle2::maxwords, 2);
    ASSERT_EQ(int_handle2::minwords, 1);
    ASSERT_EQ(int_handle4::maxbits, word_traits::bits * int_handle4::maxwords);
    ASSERT_EQ(int_handle4::minbits, word_traits::bits * int_handle4::minwords);
    ASSERT_EQ(int_handle4::maxwords, 4);
    ASSERT_EQ(int_handle4::minwords, 2);
    ASSERT_EQ(int_handle8::maxbits, word_traits::bits * int_handle8::maxwords);
    ASSERT_EQ(int_handle8::minbits, word_traits::bits * int_handle8::minwords);
    ASSERT_EQ(int_handle8::maxwords, 8);
    ASSERT_EQ(int_handle8::minwords, 4);
    int_handle2 h2;
    int_handle4 h4;
    int_handle8 h8;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unit.

TEST(int_handle, tu_int_handle_ctor_default)
{
    int_handle4 h;
    wregister hr = h.get_wregister();
    ASSERT_EQ(hr.capacity, h.minwords);
    ASSERT_EQ(hr.size, 0);
    ASSERT_EQ(hr.sign, 0);
}

TEST(int_handle, tb_int_handle_sign)
{
    int_handle4 h4;

    h4.set_sign(true);
    ASSERT_TRUE(h4.get_sign());

    h4.set_sign(false);
    ASSERT_FALSE(h4.get_sign());
}

TEST(int_handle, tb_int_handle_size)
{
    int_handle4 h4;

    h4.set_size(1);
    ASSERT_EQ(h4.get_size(), 1);

    h4.set_size(h4.get_capacity());
    ASSERT_EQ(h4.get_size(), h4.get_capacity());
}

TEST(int_handle, tb_int_handle_capacity)
{
    int_handle4 h4;

    h4.set_size(1);
    h4.set_capacity(h4.minwords + 2);
    ASSERT_EQ(h4.get_size(), 1);
    ASSERT_EQ(h4.get_capacity(), h4.minwords + 2);

    h4.set_size(h4.get_capacity());
    h4.set_capacity(h4.minwords + 1);
    ASSERT_EQ(h4.get_size(), h4.minwords + 1);
    ASSERT_EQ(h4.get_capacity(), h4.minwords + 1);

    h4.set_capacity(1);
    ASSERT_EQ(h4.get_size(), h4.minwords);
    ASSERT_EQ(h4.get_capacity(), h4.minwords);

    h4.set_size(1);
    h4.set_capacity(h4.maxwords + 1);
    ASSERT_EQ(h4.get_size(), 1);
    ASSERT_EQ(h4.get_capacity(), h4.maxwords);
}

TEST(int_handle, tu_int_handle_ctor_capacity_less)
{
    HANDLE(int_handle4, h, 1, 2, true);
    AP_REGISTER(exp, 2, 2, true, 0, 1);
    AP_ASSERT_REG(h_reg, exp);
}

TEST(int_handle, tu_int_handle_ctor_capacity_normal)
{
    HANDLE(int_handle4, h, 4, 3, false);
    AP_REGISTER(exp, 4, 3, false, 0, 1, 2);
    AP_ASSERT_REG(h_reg, exp);
}

TEST(int_handle, tu_int_handle_ctor_capacity_greater)
{
    HANDLE(int_handle4, h, 5, 3, true);
    AP_REGISTER(exp, 4, 3, true, 0, 1, 2);
    AP_ASSERT_REG(h_reg, exp);
}

TEST(int_handle, tu_int_handle_ctor_move_less)
{
    HANDLE(int_handle2, h, 2, 2, true);
    int_handle8 h8{std::move(h)};
    rregister h8_reg = h8.get_rregister();
    AP_REGISTER(exp, 4, 2, true, 0, 1);
    AP_ASSERT_REG(h8_reg, exp);
}

TEST(int_handle, tu_int_handle_ctor_move_normal)
{
    HANDLE(int_handle8, h, 6, 5, false);
    int_handle8 h8{std::move(h)};
    rregister h8_reg = h8.get_rregister();
    AP_REGISTER(exp, 6, 5, false, 0, 1, 2, 3, 4);
    AP_ASSERT_REG(h8_reg, exp);
}

TEST(int_handle, tu_int_handle_ctor_move_greater)
{
    HANDLE(int_handle8, h, 8, 8, true);
    int_handle4 h4{std::move(h)};
    rregister h4_reg = h4.get_rregister();
    AP_REGISTER(exp, 4, 4, true, 0, 1, 2, 3);
    AP_ASSERT_REG(h4_reg, exp);
}

TEST(int_handle, tu_int_handle_ctor_copy_less)
{
    HANDLE(int_handle2, h, 2, 2, true);
    int_handle8 h8{h};
    rregister h8_reg = h8.get_rregister();
    AP_REGISTER(exp, 4, 2, true, 0, 1);
    AP_ASSERT_REG(h8_reg, exp);
}

TEST(int_handle, tu_int_handle_ctor_copy_normal)
{
    HANDLE(int_handle8, h, 6, 5, false);
    int_handle8 h8{h};
    rregister h8_reg = h8.get_rregister();
    AP_REGISTER(exp, 6, 5, false, 0, 1, 2, 3, 4);
    AP_ASSERT_REG(h8_reg, exp);
}

TEST(int_handle, tu_int_handle_ctor_copy_greater)
{
    HANDLE(int_handle8, h, 8, 8, true);
    int_handle4 h4{h};
    rregister h4_reg = h4.get_rregister();
    AP_REGISTER(exp, 4, 4, true, 0, 1, 2, 3);
    AP_ASSERT_REG(h4_reg, exp);
}

TEST(int_handle, tu_int_handle_assign_move_less)
{
    HANDLE(int_handle2, h, 2, 2, true);
    int_handle8 h8;
    h8 = std::move(h);
    rregister h8_reg = h8.get_rregister();
    AP_REGISTER(exp, 4, 2, true, 0, 1);
    AP_ASSERT_REG(h8_reg, exp);
}

TEST(int_handle, tu_int_handle_assign_move_normal)
{
    HANDLE(int_handle8, h, 6, 5, false);
    int_handle8 h8;
    h8 = std::move(h);
    rregister h8_reg = h8.get_rregister();
    AP_REGISTER(exp, 6, 5, false, 0, 1, 2, 3, 4);
    AP_ASSERT_REG(h8_reg, exp);
}

TEST(int_handle, tu_int_handle_assign_move_greater)
{
    HANDLE(int_handle8, h, 8, 8, true);
    int_handle4 h4;
    h4 = std::move(h);
    rregister h4_reg = h4.get_rregister();
    AP_REGISTER(exp, 4, 4, true, 0, 1, 2, 3);
    AP_ASSERT_REG(h4_reg, exp);
}

TEST(int_handle, tu_int_handle_assign_copy_less)
{
    HANDLE(int_handle2, h, 2, 2, true);
    int_handle8 h8;
    h8 = h;
    rregister h8_reg = h8.get_rregister();
    AP_REGISTER(exp, 4, 2, true, 0, 1);
    AP_ASSERT_REG(h8_reg, exp);
}

TEST(int_handle, tu_int_handle_assign_copy_normal)
{
    HANDLE(int_handle8, h, 6, 5, false);
    int_handle8 h8;
    h8 = h;
    rregister h8_reg = h8.get_rregister();
    AP_REGISTER(exp, 6, 5, false, 0, 1, 2, 3, 4);
    AP_ASSERT_REG(h8_reg, exp);
}

TEST(int_handle, tu_int_handle_assign_copy_greater)
{
    HANDLE(int_handle8, h, 8, 8, true);
    int_handle4 h4;
    h4 = h;
    rregister h4_reg = h4.get_rregister();
    AP_REGISTER(exp, 4, 4, true, 0, 1, 2, 3);
    AP_ASSERT_REG(h4_reg, exp);
}
