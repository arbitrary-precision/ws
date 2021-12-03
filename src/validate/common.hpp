#ifndef DEOHAYER_AP_VALIDATE_UTILS_HPP
#define DEOHAYER_AP_VALIDATE_UTILS_HPP

#include <ap/int.hpp>
#include <gtest/gtest.h>
#include <type_traits>
#include <flex_debug/flex_debug.h>

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unit testing.

// Computation base.
#define AP_BASE (dword_t{word_traits::ones} + 1)

// Initialize wregister.
#define AP_REGISTER(name, capacity, size, sign, ...) \
    word_t name##_arr[capacity] = {__VA_ARGS__};     \
    wregister name { name##_arr, capacity, size, sign }

// Compare two registers.
#define AP_ASSERT_REG(reg1, reg2)                                  \
    ASSERT_EQ(reg1.sign, reg2.sign);                               \
    ASSERT_EQ(reg1.capacity, reg2.capacity);                       \
    ASSERT_EQ(reg1.size, reg2.size);                               \
    for (index_t index = 0; index < reg1.size; ++index)            \
    {                                                              \
        ASSERT_EQ(LLU(reg1.words[index]), LLU(reg2.words[index])); \
    }                                                              \
    (void)0

// All zeros.
#define AP_WZEROED (word_traits::zeros)
// All ones.
#define AP_WFILLED (word_traits::ones)
// Chess order, msb is 1.
#define AP_WCHESS1 (word_t(0xAAAAAAAA))
// Chess order, msb is 0.
#define AP_WCHESS0 (word_t(0x55555555))
// The lowest (least significant) bit.
#define AP_WONLYLB (word_t(1))
// The highest (most significant) bit.
#define AP_WONLYHB (word_t(AP_BASE / 2))
// Everything except the lowest (least significant) bit.
#define AP_WMISSLB (word_t(word_traits::ones << 1))
// Everything except the highest (most significant) bit.
#define AP_WMISSHB (word_t(word_traits::ones >> 1))
// Higher part of word_t
#define AP_WONLYHW (word_t(word_traits::ones << (word_traits::bits / 2)))
// Lower part of word_t
#define AP_WONLYLW (word_t(word_traits::ones >> (word_traits::bits / 2)))
// Human error protection. Must be set as value non-significant words (beyond the size).
#define AP_WHEPROT (word_t(0x66666666))

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Bitwise operation test suite macro.

#define AP_TEST_BIT(p, op, opf, ls, l4, l3, l2, l1, rs, r4, r3, r2, r1) \
    TEST(asm, tu_##opf##_##p)                                           \
    {                                                                   \
        word_t e1 = l1 op(rs > 0 ? r1 : AP_WZEROED);                    \
        word_t e2 = l2 op(rs > 1 ? r2 : AP_WZEROED);                    \
        word_t e3 = l3 op(rs > 2 ? r3 : AP_WZEROED);                    \
        word_t e4 = l4 op(rs > 3 ? r4 : AP_WZEROED);                    \
        AP_REGISTER(l, 4, ls, false, l1, l2, l3, l4);                   \
        AP_REGISTER(r, 4, rs, false, r1, r2, r3, r4);                   \
        AP_REGISTER(e, 4, ls, false, e1, e2, e3, e4);                   \
        AP_REGISTER(o, 4, 0, false);                                    \
        asm_##opf(rregister(l), rregister(r), o);                       \
        AP_ASSERT_REG(o, e);                                            \
    }

// Macro call structure:
// prefix, op, opf,
//         ls      l4          l3          l2          l1
//         rs      r4          r3          r2          r1
//         es      e4          e3          e2          e1
// op - operation symbol (&, |, ^).
// opf - operation function name (and, or, xor).
// l/r/e - left/right/expected
// s - size
// x4 - the most significant word
// x1 - the least significant word

#define AP_TEST_BIT_SUITE(op, opf)                                               \
                                                                                 \
    AP_TEST_BIT(zztt, op, opf,                                                   \
                0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT,               \
                0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT);              \
                                                                                 \
    AP_TEST_BIT(oztt, op, opf,                                                   \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0,               \
                0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT);              \
                                                                                 \
    AP_TEST_BIT(ozut, op, opf,                                                   \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,               \
                0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT);              \
                                                                                 \
    AP_TEST_BIT(oott, op, opf,                                                   \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0,               \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WFILLED);              \
                                                                                 \
    AP_TEST_BIT(oout, op, opf,                                                   \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,               \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1);              \
                                                                                 \
    AP_TEST_BIT(ootu, op, opf,                                                   \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0,               \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);              \
                                                                                 \
    AP_TEST_BIT(oouu, op, opf,                                                   \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED,               \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);              \
                                                                                 \
    AP_TEST_BIT(hztt, op, opf,                                                   \
                2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WCHESS0,               \
                0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT);              \
                                                                                 \
    AP_TEST_BIT(hzut, op, opf,                                                   \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,               \
                0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT);              \
                                                                                 \
    AP_TEST_BIT(hott, op, opf,                                                   \
                2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WCHESS0,               \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1);              \
                                                                                 \
    AP_TEST_BIT(hout, op, opf,                                                   \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,               \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1);              \
                                                                                 \
    AP_TEST_BIT(hotu, op, opf,                                                   \
                2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WCHESS0,               \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);              \
                                                                                 \
    AP_TEST_BIT(houu, op, opf,                                                   \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,               \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);              \
                                                                                 \
    AP_TEST_BIT(hhtt, op, opf,                                                   \
                2, AP_WHEPROT, AP_WHEPROT, AP_WFILLED, AP_WCHESS0,               \
                2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WFILLED);              \
                                                                                 \
    AP_TEST_BIT(hhut, op, opf,                                                   \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,               \
                2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WFILLED);              \
                                                                                 \
    AP_TEST_BIT(hhtu, op, opf,                                                   \
                2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS0, AP_WCHESS0,               \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED);              \
                                                                                 \
    AP_TEST_BIT(hhuu, op, opf,                                                   \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS0,               \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WFILLED);              \
                                                                                 \
    AP_TEST_BIT(fztt, op, opf,                                                   \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,               \
                0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT);              \
                                                                                 \
    AP_TEST_BIT(fzut, op, opf,                                                   \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,               \
                0, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT);              \
                                                                                 \
    AP_TEST_BIT(fott, op, opf,                                                   \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,               \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1);              \
                                                                                 \
    AP_TEST_BIT(fout, op, opf,                                                   \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,               \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1);              \
                                                                                 \
    AP_TEST_BIT(fotu, op, opf,                                                   \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,               \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);              \
                                                                                 \
    AP_TEST_BIT(fouu, op, opf,                                                   \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,               \
                1, AP_WHEPROT, AP_WHEPROT, AP_WHEPROT, AP_WZEROED);              \
                                                                                 \
    AP_TEST_BIT(fhtt, op, opf,                                                   \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,               \
                2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WCHESS1);              \
                                                                                 \
    AP_TEST_BIT(fhut, op, opf,                                                   \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,               \
                2, AP_WHEPROT, AP_WHEPROT, AP_WCHESS1, AP_WCHESS1);              \
                                                                                 \
    AP_TEST_BIT(fhtu, op, opf,                                                   \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,               \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1);              \
                                                                                 \
    AP_TEST_BIT(fhuu, op, opf,                                                   \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,               \
                2, AP_WHEPROT, AP_WHEPROT, AP_WZEROED, AP_WCHESS1);              \
                                                                                 \
    AP_TEST_BIT(fftt, op, opf,                                                   \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,               \
                4, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);              \
                                                                                 \
    AP_TEST_BIT(ffut, op, opf,                                                   \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,               \
                4, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);              \
                                                                                 \
    AP_TEST_BIT(fftu, op, opf,                                                   \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,               \
                4, AP_WZEROED, AP_WCHESS1, AP_WCHESS1, AP_WCHESS1);              \
                                                                                 \
    AP_TEST_BIT(ffuu, op, opf,                                                   \
                4, AP_WFILLED, AP_WCHESS0, AP_WFILLED, AP_WCHESS0,               \
                4, AP_WZEROED, AP_WZEROED, AP_WCHESS1, AP_WCHESS1);


// // Unsigned types: small, medium, large.
// using ap_u32 = integer<32, false>;
// using ap_u64 = integer<64, false>;
// using ap_u96 = integer<96, false>;
// // Signed types: small, medium, large.
// using ap_s32 = integer<32, true>;
// using ap_s64 = integer<64, true>;
// using ap_s96 = integer<96, true>;

// #define AP_INTT(p, size) ap_##p##size
// #define AP_INTV(p1, p2, size) p1##p2##size

// #define AP_CALL_BINARY(p1, p2, size, op)                                                      \
//     auto AP_INTV(p1, p2, size) = AP_INTT(p1, 64){1} op AP_INTT(p2, size){1};                  \
//     auto AP_INTV(p1, p2##1, size) = AP_INTT(p1, 64){1} op static_cast<bool>(1);               \
//     auto AP_INTV(p1, p2##2, size) = AP_INTT(p1, 64){1} op static_cast<char>(1);               \
//     auto AP_INTV(p1, p2##3, size) = AP_INTT(p1, 64){1} op static_cast<unsigned char>(1);      \
//     auto AP_INTV(p1, p2##4, size) = AP_INTT(p1, 64){1} op static_cast<unsigned short>(1);     \
//     auto AP_INTV(p1, p2##5, size) = AP_INTT(p1, 64){1} op static_cast<unsigned>(1);           \
//     auto AP_INTV(p1, p2##6, size) = AP_INTT(p1, 64){1} op static_cast<unsigned long>(1);      \
//     auto AP_INTV(p1, p2##7, size) = AP_INTT(p1, 64){1} op static_cast<unsigned long long>(1); \
//     auto AP_INTV(p1, p2##8, size) = AP_INTT(p1, 64){1} op static_cast<signed char>(1);        \
//     auto AP_INTV(p1, p2##9, size) = AP_INTT(p1, 64){1} op static_cast<signed short>(1);       \
//     auto AP_INTV(p1, p2##10, size) = AP_INTT(p1, 64){1} op static_cast<signed>(1);            \
//     auto AP_INTV(p1, p2##11, size) = AP_INTT(p1, 64){1} op static_cast<signed long>(1);       \
//     auto AP_INTV(p1, p2##12, size) = AP_INTT(p1, 64){1} op static_cast<signed long long>(1)

// #define AP_CALL_SELF(p1, p2, size, op)     \
//     AP_INTT(p1, 64)                        \
//     AP_INTV(p1, p2, size){1};              \
//     AP_INTV(p1, p2, size)                  \
//     op AP_INTT(p2, size){1};               \
//     AP_INTT(p1, 64)                        \
//     AP_INTV(p1, p2##1, size){1};           \
//     AP_INTV(p1, p2##1, size)               \
//     op static_cast<bool>(1);               \
//     AP_INTT(p1, 64)                        \
//     AP_INTV(p1, p2##2, size){1};           \
//     AP_INTV(p1, p2##2, size)               \
//     op static_cast<char>(1);               \
//     AP_INTT(p1, 64)                        \
//     AP_INTV(p1, p2##3, size){1};           \
//     AP_INTV(p1, p2##3, size)               \
//     op static_cast<unsigned char>(1);      \
//     AP_INTT(p1, 64)                        \
//     AP_INTV(p1, p2##4, size){1};           \
//     AP_INTV(p1, p2##4, size)               \
//     op static_cast<unsigned short>(1);     \
//     AP_INTT(p1, 64)                        \
//     AP_INTV(p1, p2##5, size){1};           \
//     AP_INTV(p1, p2##5, size)               \
//     op static_cast<unsigned>(1);           \
//     AP_INTT(p1, 64)                        \
//     AP_INTV(p1, p2##6, size){1};           \
//     AP_INTV(p1, p2##6, size)               \
//     op static_cast<unsigned long>(1);      \
//     AP_INTT(p1, 64)                        \
//     AP_INTV(p1, p2##7, size){1};           \
//     AP_INTV(p1, p2##7, size)               \
//     op static_cast<unsigned long long>(1); \
//     AP_INTT(p1, 64)                        \
//     AP_INTV(p1, p2##8, size){1};           \
//     AP_INTV(p1, p2##8, size)               \
//     op static_cast<signed char>(1);        \
//     AP_INTT(p1, 64)                        \
//     AP_INTV(p1, p2##9, size){1};           \
//     AP_INTV(p1, p2##9, size)               \
//     op static_cast<signed short>(1);       \
//     AP_INTT(p1, 64)                        \
//     AP_INTV(p1, p2##10, size){1};          \
//     AP_INTV(p1, p2##10, size)              \
//     op static_cast<signed>(1);             \
//     AP_INTT(p1, 64)                        \
//     AP_INTV(p1, p2##11, size){1};          \
//     AP_INTV(p1, p2##11, size)              \
//     op static_cast<signed long>(1);        \
//     AP_INTT(p1, 64)                        \
//     AP_INTV(p1, p2##12, size){1};          \
//     AP_INTV(p1, p2##12, size)              \
//     op static_cast<signed long long>(1)

// #define AP_CALL_PRE(p, op)    \
//     AP_INTT(p, 64)            \
//     AP_INTV(p, pre, size){1}; \
//     op AP_INTV(p, pre, size)

// #define AP_CALL_POST(p, op)    \
//     AP_INTT(p, 64)             \
//     AP_INTV(p, post, size){1}; \
//     AP_INTV(p, post, size)     \
//     op

#endif
