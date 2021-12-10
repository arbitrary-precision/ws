#ifndef DEOHAYER_AP_VALIDATE_COMMON_HPP
#define DEOHAYER_AP_VALIDATE_COMMON_HPP

#include <ap/ap.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <flex_debug/flex_debug.h>
#include <gtest/gtest.h>
#include <type_traits>

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common defines, can by used everywhere.

// word_t patterns as integer values (may be bigger then word_t, but wrapping does the trick)
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

// Initialize wregister.
#define AP_REGISTER(name, capacity, size, sign, ...) \
    word_t name##_arr[capacity] = {__VA_ARGS__};     \
    wregister name { name##_arr, capacity, size, sign }

// Initialize wregister.
#define AP_REGISTER_D(name, capacity)                         \
    array<word_t> name##_arr = array_alloc<word_t>(capacity); \
    wregister name { name##_arr.get(), capacity, 0, false }

// Compare two registers.
#define AP_ASSERT_REG(reg1, reg2)                                  \
    ASSERT_EQ(reg1.sign, reg2.sign);                               \
    ASSERT_EQ(reg1.capacity, reg2.capacity);                       \
    ASSERT_EQ(reg1.size, reg2.size);                               \
    for (index_t index = 0; index < reg1.size; ++index)            \
    {                                                              \
        ASSERT_EQ(reg1.words[index], reg2.words[index]); \
    }                                                              \
    (void)0

// Print register (for debugging).
#define AP_PRINT_REG(reg)                                                                                   \
    std::cout << "REG " #reg ":" << (reg.sign ? " - " : " + ") << reg.capacity << " " << reg.size << " [ "; \
    for (index_t index = reg.size; index > 0;)                                                              \
    {                                                                                                       \
        --index;                                                                                            \
        std::cout << std::hex << static_cast<unsigned long long>(reg.words[index]) << " ";                                              \
    }                                                                                                       \
    std::cout << "]" << std::dec << std::endl

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common defines, but used on int- and user-level API (*api_* functions, integer class interface)

//
// Capacity use cases
//

#define AP_CAP_S 256
#define AP_CAP_L 512

// Get capacity in bytes.
static inline constexpr index_t ap_capb(index_t cap)
{
    return cap / CHAR_BIT;
}

// Get capacity in words.
static inline constexpr index_t ap_capw(index_t cap)
{
    return (cap / CHAR_BIT) / word_traits::bytes;
}

// Size use cases. Note that those are in words.
// They and are not applicable to one-word capacity.

// Size of one word
#define AP_SZ_O 9
// Size of one fourth capacity
#define AP_SZ_Q 1
// Size of half capacity
#define AP_SZ_H 2
// Size of three fourths of the capacity (most)
#define AP_SZ_M 3
// Size of full capacity
#define AP_SZ_F 4

// Size in bits.
static inline constexpr index_t ap_sz(index_t cap, index_t sz)
{
    return (sz == AP_SZ_O) ? word_traits::bits : (cap / 4) * sz;
}

// Size in bytes.
static inline constexpr index_t ap_szb(index_t cap, index_t sz)
{
    return ap_sz(cap, sz) / CHAR_BIT;
}

// Size in words.
static inline constexpr index_t ap_szw(index_t cap, index_t sz)
{
    return ap_szb(cap, sz) / word_traits::bytes;
}

// Byte pattern types. Binary form: "00000000", "01010101", "10101010", "11111111"

// Zeroed        "00000000"
#define AP_BP_ZD 0
// Chess type 0  "01010101"
#define AP_BP_C0 2
// Chess type 1  "10101010"
#define AP_BP_C1 1
// Filled        "11111111"
#define AP_BP_FD 3

// Get actual string for the given single byte pattern.
static inline std::string ap_bp(index_t bp)
{
    static const std::string bstrs[4] = {"00", "AA", "55", "FF"};
    return bstrs[bp];
}

// String patterns.

// Zeroed
#define AP_SP_ZD 0 // "00000000 00000000 ... 00000000 00000000"
// Chess type 0 (small)
#define AP_SP_C0 1 // "01010101 01010101 ... 01010101 01010101"
// Chess type 1 (small)
#define AP_SP_C1 2 // "10101010 10101010 ... 10101010 10101010"
// Chess type 2 (big)
#define AP_SP_C2 3 // "00000000 11111111 ... 00000000 11111111"
// Chess type 3 (big)
#define AP_SP_C3 4 // "11111111 00000000 ... 11111111 00000000"
// Only lowest bit
#define AP_SP_OL 5 // "00000000 00000000 ... 00000000 00000001"
// Only highest bit
#define AP_SP_OH 6 // "10000000 00000000 ... 00000000 00000000"
// Missing lowest bit
#define AP_SP_ML 7 // "11111111 11111111 ... 11111111 11111110"
// Missing highest bit
#define AP_SP_MH 8 // "01111111 11111111 ... 11111111 11111111"
// Filled
#define AP_SP_FD 9 // "11111111 11111111 ... 11111111 11111111"

// Get actual pattern with a given bit capacity.
static inline std::string ap_sp(index_t cap, index_t sp)
{
    std::string result;
    std::string byte0;
    std::string byte1;

    if (cap == 0)
    {
        return "0";
    }

    if ((cap % 8) != 0)
    {
        throw std::runtime_error("ap_sp: cap is not aligned to 8.");
    }

    cap /= 8;

    switch (sp)
    {
    case AP_SP_ZD:
    {
        return std::string(cap * 2, '0');
    }
    case AP_SP_FD:
    {
        return std::string(cap * 2, 'F');
    }
    case AP_SP_C0:
    {
        byte0 = ap_bp(AP_BP_C0);
        byte1 = ap_bp(AP_BP_C0);
        break;
    }
    case AP_SP_C1:
    {
        byte0 = ap_bp(AP_BP_C1);
        byte1 = ap_bp(AP_BP_C1);
        break;
    }
    case AP_SP_C2:
    {
        byte0 = ap_bp(AP_BP_ZD);
        byte1 = ap_bp(AP_BP_FD);
        break;
    }
    case AP_SP_C3:
    {
        byte0 = ap_bp(AP_BP_FD);
        byte1 = ap_bp(AP_BP_ZD);
        break;
    }
    case AP_SP_OL:
    {
        byte0 = ap_bp(AP_BP_ZD);
        byte1 = ap_bp(AP_BP_ZD);
        break;
    }
    case AP_SP_OH:
    {
        byte0 = ap_bp(AP_BP_ZD);
        byte1 = ap_bp(AP_BP_ZD);
        break;
    }
    case AP_SP_ML:
    {
        byte0 = ap_bp(AP_BP_FD);
        byte1 = ap_bp(AP_BP_FD);
        break;
    }
    case AP_SP_MH:
    {
        byte0 = ap_bp(AP_BP_FD);
        byte1 = ap_bp(AP_BP_FD);
        break;
    }
    default:
        throw std::runtime_error("ap_sp: wrong pattern type.");
    }

    for (index_t i = 0; i < cap; ++i)
    {
        result += ((i % 2) ? byte1 : byte0);
    }

    switch (sp)
    {
    case AP_SP_OL:
    {
        result[result.size() - 1] = '1';
        break;
    }
    case AP_SP_OH:
    {
        result[0] = '8';
        break;
    }
    case AP_SP_ML:
    {
        result[result.size() - 1] = 'E';
        break;
    }
    case AP_SP_MH:
    {
        result[0] = '7';
        break;
    }
    default:
        break;
    }

    return result;
}

// Unified representation.

using boost_uint = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<AP_CAP_L, AP_CAP_L, boost::multiprecision::unsigned_magnitude, boost::multiprecision::unchecked, void>>;
using boost_sint = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<AP_CAP_L, AP_CAP_L, boost::multiprecision::signed_magnitude, boost::multiprecision::unchecked, void>>;

// Translate any value to unsigned with the given capacity.
static inline std::string ap_tu(std::string str, index_t cap)
{
    boost_uint v{str};
    str = v.str(0, std::ios_base::hex | std::ios_base::uppercase);
    // Capacity in symbols.
    cap = ap_capb(cap) * 2;
    if (str.size() > cap)
    {
        str = "0x" + str.substr(str.size() - cap, cap);
        // This removes leading zeroes.
        v.assign(str);
        str = v.str(0, std::ios_base::hex | std::ios_base::uppercase);
    }
    return std::string("0x") + str;
}

// Translate any value to signed with the given capacity.
static inline std::string ap_ts(std::string str, index_t cap)
{
    str = ap_tu(str, cap);
    if (str.size() == (ap_capb(cap) * 2 + 2))
    {
        if (str[2] == '8' || str[2] == '9' || str[2] == 'A' || str[2] == 'B' || str[2] == 'C' || str[2] == 'D' || str[2] == 'E' || str[2] == 'F')
        {
            boost_uint v{str};
            v = ~v + 1;
            str = "-" + ap_tu("0x" + v.str(0, std::ios_base::hex | std::ios_base::uppercase), cap);
        }
    }
    return str;
}

// Unsigned value generation with the given capacity and pattern.
static inline std::string ap_gu(index_t cap, index_t sp)
{
    return ap_tu(std::string("0x") + ap_sp(cap, sp), cap);
}

// Signed value generation with the given capacity and pattern.
static inline std::string ap_gs(index_t cap, index_t sp)
{
    return ap_ts(ap_gu(cap, sp), cap);
}

static inline std::string boost_uint_tos(const boost_uint& v, index_t oc)
{
    return ap_ts(std::string("0x") + v.str(0, std::ios_base::hex | std::ios_base::uppercase), oc);
}

static inline std::string boost_uint_tou(const boost_uint& v, index_t oc)
{
    return ap_tu(std::string("0x") + v.str(0, std::ios_base::hex | std::ios_base::uppercase), oc);
}

static inline unsigned long long to_ull(const std::string& str)
{
    return std::stoull(ap_tu(str, sizeof(unsigned long long) * CHAR_BIT), nullptr, 16);
}

// Testing macros

#define BOOST_BOP(name, oper, sgnd)                                                                                                       \
    static inline std::string boost_##name##_##sgnd(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc) \
    {                                                                                                                                     \
        boost_uint lv{lstr};                                                                                                              \
        boost_uint rv{rstr};                                                                                                              \
        boost_uint ov = lv oper rv;                                                                                                       \
        return boost_uint_to##sgnd(ov, oc);                                                                                               \
    }

// Binary operation

#define TEST_BOP_STEP(name, sgnd, lc, ls, lp, rc, rs, rp, oc)           \
    std::string lstr = ap_g##sgnd(ap_sz(lc, ls), lp);                   \
    std::string rstr = ap_g##sgnd(ap_sz(rc, rs), rp);                   \
    std::string estr = boost_##name##_##sgnd(lstr, rstr, lc, rc, oc);   \
    std::string ostr = ap_##name##_##sgnd(lstr, rstr, lc, rc, oc);      \
    if (estr != ostr)                                                   \
    {                                                                   \
        std::cout << "Failed patterns " << lp << " and " << rp << "\n"; \
        std::cout << "lstr: " << lstr << "\n";                          \
        std::cout << "rstr: " << rstr << "\n";                          \
        std::cout << "estr: " << estr << "\n";                          \
        std::cout << "ostr: " << ostr << "\n";                          \
        ASSERT_FALSE(true);                                             \
    }

#define TEST_BOP_SINGLE(name, sgnd, lc, ls, lp, rc, rs, rp, oc) \
    TEST(name, single)                                          \
    {                                                           \
        TEST_BOP_STEP(name, sgnd, lc, ls, lp, rc, rs, rp, oc);  \
    }

#define TEST_BOP(sfx, name, sgnd, lc, ls, rc, rs, oc)                \
    TEST(name, sgnd##_##sfx)                                         \
    {                                                                \
        for (index_t i = 0; i < 10; ++i)                             \
        {                                                            \
            for (index_t j = 0; j < 10; ++j)                         \
            {                                                        \
                TEST_BOP_STEP(name, sgnd, lc, ls, i, rc, rs, j, oc); \
            }                                                        \
        }                                                            \
    }

#define TEST_BOP_SZ_R(sfx, name, sgnd, lc, ls, rc, oc)     \
    TEST_BOP(sfx##O, name, sgnd, lc, ls, rc, AP_SZ_O, oc); \
    TEST_BOP(sfx##Q, name, sgnd, lc, ls, rc, AP_SZ_Q, oc); \
    TEST_BOP(sfx##H, name, sgnd, lc, ls, rc, AP_SZ_H, oc); \
    TEST_BOP(sfx##M, name, sgnd, lc, ls, rc, AP_SZ_M, oc); \
    TEST_BOP(sfx##F, name, sgnd, lc, ls, rc, AP_SZ_F, oc);

#define TEST_BOP_SZ(sfx, name, sgnd, lc, rc, oc)             \
    TEST_BOP_SZ_R(sfx##_O, name, sgnd, lc, AP_SZ_O, rc, oc); \
    TEST_BOP_SZ_R(sfx##_Q, name, sgnd, lc, AP_SZ_Q, rc, oc); \
    TEST_BOP_SZ_R(sfx##_H, name, sgnd, lc, AP_SZ_H, rc, oc); \
    TEST_BOP_SZ_R(sfx##_M, name, sgnd, lc, AP_SZ_M, rc, oc); \
    TEST_BOP_SZ_R(sfx##_F, name, sgnd, lc, AP_SZ_F, rc, oc);

#define TEST_SUITE_BOP(name, sgnd)                              \
    TEST_BOP_SZ(LLL, name, sgnd, AP_CAP_L, AP_CAP_L, AP_CAP_L); \
    TEST_BOP_SZ(LLS, name, sgnd, AP_CAP_L, AP_CAP_L, AP_CAP_S); \
    TEST_BOP_SZ(LSL, name, sgnd, AP_CAP_L, AP_CAP_S, AP_CAP_L); \
    TEST_BOP_SZ(LSS, name, sgnd, AP_CAP_L, AP_CAP_S, AP_CAP_S); \
    TEST_BOP_SZ(SLL, name, sgnd, AP_CAP_S, AP_CAP_L, AP_CAP_L); \
    TEST_BOP_SZ(SLS, name, sgnd, AP_CAP_S, AP_CAP_L, AP_CAP_S); \
    TEST_BOP_SZ(SSL, name, sgnd, AP_CAP_S, AP_CAP_S, AP_CAP_L); \
    TEST_BOP_SZ(SSS, name, sgnd, AP_CAP_S, AP_CAP_S, AP_CAP_S);

// Unary operation

#define TEST_UOP_STEP(name, sgnd, ic, is, ip, oc)           \
    std::string istr = ap_g##sgnd(ap_sz(ic, is), ip);       \
    std::string estr = boost_##name##_##sgnd(istr, ic, oc); \
    std::string ostr = ap_##name##_##sgnd(istr, ic, oc);    \
    if (estr != ostr)                                       \
    {                                                       \
        std::cout << "Failed pattern " << ip << "\n";       \
        std::cout << "istr: " << istr << "\n";              \
        std::cout << "estr: " << estr << "\n";              \
        std::cout << "ostr: " << ostr << "\n";              \
        ASSERT_FALSE(true);                                 \
    }

#define TEST_UOP_SINGLE(name, sgnd, ic, is, ip, oc) \
    TEST(name, single)                              \
    {                                               \
        TEST_UOP_STEP(name, sgnd, ic, is, ip, oc);  \
    }

#define TEST_UOP(sfx, name, sgnd, ic, is, oc)         \
    TEST(name, sgnd##_##sfx)                          \
    {                                                 \
        for (index_t i = 0; i < 10; ++i)              \
        {                                             \
            TEST_UOP_STEP(name, sgnd, ic, is, i, oc); \
        }                                             \
    }

#define TEST_UOP_SZ(sfx, name, sgnd, ic, oc)        \
    TEST_UOP(sfx##_O, name, sgnd, ic, AP_SZ_O, oc); \
    TEST_UOP(sfx##_Q, name, sgnd, ic, AP_SZ_Q, oc); \
    TEST_UOP(sfx##_H, name, sgnd, ic, AP_SZ_H, oc); \
    TEST_UOP(sfx##_M, name, sgnd, ic, AP_SZ_M, oc); \
    TEST_UOP(sfx##_F, name, sgnd, ic, AP_SZ_F, oc);

#define TEST_SUITE_UOP(name, sgnd)                   \
    TEST_UOP_SZ(LL, name, sgnd, AP_CAP_L, AP_CAP_L); \
    TEST_UOP_SZ(LS, name, sgnd, AP_CAP_L, AP_CAP_S); \
    TEST_UOP_SZ(SL, name, sgnd, AP_CAP_S, AP_CAP_L); \
    TEST_UOP_SZ(SS, name, sgnd, AP_CAP_S, AP_CAP_S);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common defines, but only user-level API (integer class interface)

#define TEST_SUITE_BOPERATOR(name, sgnd)                        \
    TEST_BOP_SZ(LLL, name, sgnd, AP_CAP_L, AP_CAP_L, AP_CAP_L); \
    TEST_BOP_SZ(LSL, name, sgnd, AP_CAP_L, AP_CAP_S, AP_CAP_L); \
    TEST_BOP_SZ(LSS, name, sgnd, AP_CAP_L, AP_CAP_S, AP_CAP_S); \
    TEST_BOP_SZ(SLL, name, sgnd, AP_CAP_S, AP_CAP_L, AP_CAP_L); \
    TEST_BOP_SZ(SLS, name, sgnd, AP_CAP_S, AP_CAP_L, AP_CAP_S); \
    TEST_BOP_SZ(SSS, name, sgnd, AP_CAP_S, AP_CAP_S, AP_CAP_S);

using ap_uint_l = integer<AP_CAP_L, false>;
using ap_uint_s = integer<AP_CAP_S, false>;
using ap_sint_l = integer<AP_CAP_L, true>;
using ap_sint_s = integer<AP_CAP_S, true>;

template <bool _Signed, template <index_t, bool> typename Oper>
std::string ap_dispatch_unary_op(const std::string& istr, index_t ic)
{
    std::string result;
    if (ic == AP_CAP_L)
    {
        Oper<AP_CAP_L, _Signed> oper;
        result = oper(istr);
    }
    else
    {
        Oper<AP_CAP_S, _Signed> oper;
        result = oper(istr);
    }
    return result;
}

template <bool _Signed, template <index_t, index_t, bool> typename Oper>
std::string ap_dispatch_binary_op(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    std::string result;

    if (lc == AP_CAP_L)
    {
        if (rc == AP_CAP_L)
        {
            Oper<AP_CAP_L, AP_CAP_L, _Signed> oper;
            result = oper(lstr, rstr);
        }
        else
        {
            Oper<AP_CAP_L, AP_CAP_S, _Signed> oper;
            result = oper(lstr, rstr);
        }
    }
    else
    {
        if (rc == AP_CAP_L)
        {
            Oper<AP_CAP_S, AP_CAP_L, _Signed> oper;
            result = oper(lstr, rstr);
        }
        else
        {
            Oper<AP_CAP_S, AP_CAP_S, _Signed> oper;
            result = oper(lstr, rstr);
        }
    }

    return result;
}

#endif
