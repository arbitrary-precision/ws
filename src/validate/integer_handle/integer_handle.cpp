#include "../common.hpp"

using word_handle2 = integer_handle<dword_traits::bits>;
using word_handle4 = integer_handle<dword_traits::bits * 2>;
using word_handle8 = integer_handle<dword_traits::bits * 4>;

#define HANDLE(_type, _name, _capacity, _size, _sign) \
    _type _name{};                                    \
    _name.set_size(_size);                            \
    _name.set_sign(_sign);                            \
    wregister _name##_reg = _name.get_wregister();    \
    for (index_t i = 0; i < _name##_reg.size; ++i)    \
    {                                                 \
        _name##_reg.words[i] = word_t(i);             \
    }

TEST(integer_handle, build)
{
    ASSERT_EQ(word_handle2::bitwidth, word_traits::bits * word_handle2::wordwidth);
    ASSERT_EQ(word_handle2::wordwidth, 2);
    ASSERT_EQ(word_handle4::bitwidth, word_traits::bits * word_handle4::wordwidth);
    ASSERT_EQ(word_handle4::wordwidth, 4);
    ASSERT_EQ(word_handle8::bitwidth, word_traits::bits * word_handle8::wordwidth);
    ASSERT_EQ(word_handle8::wordwidth, 8);
    word_handle2 h2;
    word_handle4 h4;
    word_handle8 h8;
}

TEST(integer_handle, ctor_d)
{
    word_handle4 h;
    wregister hr = h.get_wregister();
    ASSERT_EQ(hr.size, 0);
    ASSERT_EQ(hr.sign, 0);
}

TEST(integer_handle, sign)
{
    word_handle4 h4;

    h4.set_sign(true);
    ASSERT_TRUE(h4.get_sign());

    h4.set_sign(false);
    ASSERT_FALSE(h4.get_sign());
}

TEST(integer_handle, size)
{
    word_handle4 h4;

    h4.set_size(1);
    ASSERT_EQ(h4.get_size(), 1);

    h4.set_size(2);
    ASSERT_EQ(h4.get_size(), 2);
}

TEST(integer_handle, capacity)
{
    word_handle4 h4;

    h4.set_size(1);
    ASSERT_EQ(h4.get_size(), 1);

    h4.set_size(h4.get_capacity());
    ASSERT_EQ(h4.get_size(), 4);
}

TEST(integer_handle, ctor_move_less)
{
    HANDLE(word_handle2, h, 2, 2, true);
    word_handle8 h8{std::move(h)};
    rregister h8_reg = h8.get_rregister();
    AP_REGISTER(exp, 8, 2, true, 0, 1);
    AP_ASSERT_REG(h8_reg, exp);
}

TEST(integer_handle, ctor_move_normal)
{
    HANDLE(word_handle8, h, 6, 5, false);
    word_handle8 h8{std::move(h)};
    rregister h8_reg = h8.get_rregister();
    AP_REGISTER(exp, 8, 5, false, 0, 1, 2, 3, 4);
    AP_ASSERT_REG(h8_reg, exp);
}

TEST(integer_handle, ctor_move_greater)
{
    HANDLE(word_handle8, h, 8, 8, true);
    word_handle4 h4{std::move(h)};
    rregister h4_reg = h4.get_rregister();
    AP_REGISTER(exp, 4, 4, true, 0, 1, 2, 3);
    AP_ASSERT_REG(h4_reg, exp);
}

TEST(integer_handle, ctor_copy_less)
{
    HANDLE(word_handle2, h, 2, 2, true);
    word_handle8 h8{h};
    rregister h8_reg = h8.get_rregister();
    AP_REGISTER(exp, 8, 2, true, 0, 1);
    AP_ASSERT_REG(h8_reg, exp);
}

TEST(integer_handle, ctor_copy_normal)
{
    HANDLE(word_handle8, h, 6, 5, false);
    word_handle8 h8{h};
    rregister h8_reg = h8.get_rregister();
    AP_REGISTER(exp, 8, 5, false, 0, 1, 2, 3, 4);
    AP_ASSERT_REG(h8_reg, exp);
}

TEST(integer_handle, ctor_copy_greater)
{
    HANDLE(word_handle8, h, 8, 8, true);
    word_handle4 h4{h};
    rregister h4_reg = h4.get_rregister();
    AP_REGISTER(exp, 4, 4, true, 0, 1, 2, 3);
    AP_ASSERT_REG(h4_reg, exp);
}

TEST(integer_handle, assign_move_less)
{
    HANDLE(word_handle2, h, 2, 2, true);
    word_handle8 h8;
    h8 = std::move(h);
    rregister h8_reg = h8.get_rregister();
    AP_REGISTER(exp, 8, 2, true, 0, 1);
    AP_ASSERT_REG(h8_reg, exp);
}

TEST(integer_handle, assign_move_normal)
{
    HANDLE(word_handle8, h, 6, 5, false);
    word_handle8 h8;
    h8 = std::move(h);
    rregister h8_reg = h8.get_rregister();
    AP_REGISTER(exp, 8, 5, false, 0, 1, 2, 3, 4);
    AP_ASSERT_REG(h8_reg, exp);
}

TEST(integer_handle, assign_move_greater)
{
    HANDLE(word_handle8, h, 8, 8, true);
    word_handle4 h4;
    h4 = std::move(h);
    rregister h4_reg = h4.get_rregister();
    AP_REGISTER(exp, 4, 4, true, 0, 1, 2, 3);
    AP_ASSERT_REG(h4_reg, exp);
}

TEST(integer_handle, assign_copy_less)
{
    HANDLE(word_handle2, h, 2, 2, true);
    word_handle8 h8;
    h8 = h;
    rregister h8_reg = h8.get_rregister();
    AP_REGISTER(exp, 8, 2, true, 0, 1);
    AP_ASSERT_REG(h8_reg, exp);
}

TEST(integer_handle, assign_copy_normal)
{
    HANDLE(word_handle8, h, 6, 5, false);
    word_handle8 h8;
    h8 = h;
    rregister h8_reg = h8.get_rregister();
    AP_REGISTER(exp, 8, 5, false, 0, 1, 2, 3, 4);
    AP_ASSERT_REG(h8_reg, exp);
}

TEST(integer_handle, assign_copy_greater)
{
    HANDLE(word_handle8, h, 8, 8, true);
    word_handle4 h4;
    h4 = h;
    rregister h4_reg = h4.get_rregister();
    AP_REGISTER(exp, 4, 4, true, 0, 1, 2, 3);
    AP_ASSERT_REG(h4_reg, exp);
}
