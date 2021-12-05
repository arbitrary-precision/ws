#ifndef DEOHAYER_AP_VALIDATE_UTILS_HPP
#define DEOHAYER_AP_VALIDATE_UTILS_HPP

#include <ap/int.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <flex_debug/flex_debug.h>
#include <gtest/gtest.h>
#include <type_traits>

using namespace ap::library;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common defines, used everywhere.

// Sign constants.
// Positive, mnemonic in test name is u
#define AP_P false
// Negative, mnemonic in test name is s
#define AP_N true

// Signedness prefix.
// No sign
#define AP_S s
// Has sign
#define AP_U u

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

// Print register (for debugging).
#define AP_PRINT_REG(reg)                                                                                   \
    std::cout << "REG " #reg ":" << (reg.sign ? " - " : " + ") << reg.capacity << " " << reg.size << " [ "; \
    for (index_t index = reg.size; index > 0;)                                                              \
    {                                                                                                       \
        --index;                                                                                            \
        std::cout << std::hex << LLU(reg.words[index]) << " ";                                              \
    }                                                                                                       \
    std::cout << "]" << std::dec << std::endl

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Common defines, but used on int and user level API (integer interface, xint_* functions)

// Capacity use cases (in bytes). Minimum possible (1 word), maximum (custom) and somewhere in the middle.
enum apt_cap
{
    CMIN,
    CMID,
    CMAX,
    COUNT
};

#define AP_MIN_CAP word_traits::bytes
#define AP_MID_CAP 16
#define AP_MAX_CAP 32

// Get actual capacity in bytes.
static inline index_t apt_gcap(apt_cap c)
{
    static const index_t cs[apt_cap::COUNT] = {AP_MIN_CAP, AP_MID_CAP, AP_MAX_CAP};
    return cs[c];
}

// Get actual capacity in words.
static inline index_t apt_gcapw(apt_cap c)
{
    return apt_gcap(c) / word_traits::bytes;
}

// Size use cases: zero, one, half of capacity, full capacity.
enum apt_size
{
    SZ, // z mnemonic in unit test name
    SO, // o mnemonic in unit test name
    SH, // h mnemonic in unit test name
    SF, // f mnemonic in unit test name
    SCOUNT
};

// Size in bytes.
static inline index_t apt_gsize(apt_size s, apt_cap c)
{
    switch (s)
    {
    case apt_size::SZ:
        return 0;
    case apt_size::SO:
        return 1;
    case apt_size::SH:
        return (apt_gcap(c) / 2);
    case apt_size::SF:
        return apt_gcap(c);
    default:
        throw std::invalid_argument("apt_gsizew defaulted.");
    }
}

// Size in words.
static inline index_t apt_gsizew(apt_size s, apt_cap c)
{
    return apt_gsizew(s, c) / word_traits::bytes;
}

// Byte patterns. Binary form: "00000000", "01010101", "10101010", "11111111"
enum apt_bstr
{
    BZEROED,
    BCHESS0,
    BCHESS1,
    BFILLED,
    BCOUNT
};

// Get actual string for the given single byte pattern.
static inline std::string apt_gbstr(apt_bstr b)
{
    static const std::string bstrs[apt_bstr::BCOUNT] = {"00", "55", "AA", "FF"};
    return bstrs[b];
}

// String patterns.
enum apt_pat
{
    PFILLED, // "1111...1111"
    PCHESS0, // "0101...0101"
    PCHESS1, // "1010...1010"
    PZEROED, // "0000...0000"
    PONLYLB, // "0000...0001"
    PONLYHB, // "1000...0000"
    PMISSLB, // "1111...1110"
    PMISSHB, // "0111...1111"
    PCOUNT
};

// Get actual pattern with a given byte size.
static inline std::string apt_gpstr(apt_pat p, index_t s)
{
    std::string pstr = "0x";
    std::string bstr0;
    std::string bstr1;
    switch (p)
    {
    case PFILLED:
    case PMISSHB:
    case PMISSLB:
        bstr0 = apt_gbstr(apt_bstr::BFILLED);
        bstr1 = apt_gbstr(apt_bstr::BFILLED);
        break;
    case PCHESS0:
        bstr0 = apt_gbstr(apt_bstr::BCHESS0);
        bstr1 = apt_gbstr(apt_bstr::BCHESS0);
        break;
    case PCHESS1:
        bstr0 = apt_gbstr(apt_bstr::BCHESS1);
        bstr1 = apt_gbstr(apt_bstr::BCHESS1);
        break;
    case PZEROED:
    case PONLYLB:
    case PONLYHB:
        bstr0 = apt_gbstr(apt_bstr::BZEROED);
        bstr1 = apt_gbstr(apt_bstr::BZEROED);
        break;
    default:
        break;
    }
    pstr += bstr0;
    for (index_t i = 1; i < s; ++i)
    {
        pstr += bstr1;
    }
    if (p == apt_pat::PONLYHB)
    {
        pstr[2] = '8';
    }
    else if (p == apt_pat::PONLYLB)
    {
        pstr[pstr.size() - 1] = '1';
    }
    else if (p == apt_pat::PMISSHB)
    {
        pstr[2] = '7';
    }
    else if (p == apt_pat::PMISSLB)
    {
        pstr[pstr.size() - 1] = 'E';
    }
    return pstr;
}

// Get two's complement string pattern for given size, capacity and sign.

using boost_uint = boost::multiprecision::uint1024_t;
using boost_int = boost::multiprecision::int1024_t;

// Normal view, without leading zeros.
static inline std::string apt_norm(std::string str, apt_cap c, apt_size s)
{
    boost_uint val;
    index_t bsize = apt_gsize(s, c);
    if (bsize * 2 < (str.size() - 2))
    {
        str = std::string("0x") + str.substr(str.size() - bsize * 2, bsize * 2);
    }
    val.assign(str);
    return std::string("0x") + val.str(0, std::ios_base::hex);
}

// Two's complement of the given string.
static inline std::string apt_twos(std::string str)
{
    boost_uint val;
    val.assign(str);
    val = ~val + 1;
    str = std::string("0x") + val.str(0, std::ios_base::hex);
    return str;
}

// Transform two's complement pattern to sign and magnitude; sgn means that '-' should be applied to non-negative value represented by str.
static inline std::string apt_stru(std::string str, apt_cap c, apt_size s, bool sgn = false)
{
    if (sgn)
    {
        str = apt_twos(str);
    }
    return apt_norm(str, c, s);
}

// Cast string to signed with sign and slice it.
static inline std::string apt_strs(std::string str, apt_cap c, apt_size s)
{
    str = apt_norm(str, c, s);
    if ((str.size() - 2) == (apt_gcap(c) * 2))
    {
        if (str[2] == '8' || str[2] == '9' || str[2] == 'A' || str[2] == 'B' || str[2] == 'C' || str[2] == 'D' || str[2] == 'E' || str[2] == 'F')
        {
            for (index_t i = 3; i < str.size(); ++i)
            {
                str = apt_twos(str);
                str = apt_norm(str, c, s);
                str = "-" + str;
            }
        }
    }
    return str;
}

// Generate bit pattern p for the given capacity, size and sign.
static inline std::string apt_strp(apt_pat p, apt_cap c, apt_size s, bool sgn)
{
    index_t bsize = apt_gsize(s, c);
    return apt_stru(apt_gpstr(p, apt_gsize(s, c)), c, s, sgn);
}

// Test case suffix:
// [left mnemonic] [left size] _ [right mnemonic] [right size] _ [capacity mnemonic] [left sign] [right sign]

// x mnemonic:
// fd - PFILLED
// c0 - PCHESS0
// c1 - PCHESS1
// zd - PZEROED
// mh - PMISSHB
// ml - PMISSLB
// oh - PONLYHB
// ol - PONLYHB

// capacity mnemonic:
// mx - max
// md - mid
// mn - min

// size:
// z - zero
// o - one
// h - half
// f - full

// sign
// u - unsigned
// s - signed

// Test case, both parameters can be configured.
// suffix
// operation
// signedness of the operation
// out capacity
// left sign
// left pattern
// left size
// right sign
// right pattern
// right size
#define TEST_BIN_OP(sfx, op, sgnd, oc, lsgn, lp, ls, rsgn, rp, rs)                          \
    TEST(xapi_##op, sfx)                                                                    \
    {                                                                                       \
        std::string lstr = apt_strp(lp, apt_cap::CMAX, ls, lsgn);                           \
        std::string rstr = apt_strp(rp, apt_cap::CMAX, rs, rsgn);                           \
        std::string estr = apt_str##sgnd(bapi_##op##_##sgnd(lstr, rstr), oc, apt_size::SF); \
        std::string ostr = xapi_##op##_##sgnd(lstr, rstr, oc);                              \
        ASSERT_EQ(ostr, estr);                                                              \
    }

// Suite step, left parameter parametrized, right is fixed).
// suffix
// operation
// signedness of the operation
// out capacity
// left sign
// left pattern
// left size
// right sign
#define TEST_BIN_OP_SUITE_STEP(sfx, op, sgnd, oc, lsgn, lp, ls, rsgn)                         \
    TEST_BIN_OP(sfx##_fdf, op, sgnd, oc, lsgn, lp, ls, rsgn, apt_pat::PFILLED, apt_size::SF); \
    TEST_BIN_OP(sfx##_fdh, op, sgnd, oc, lsgn, lp, ls, rsgn, apt_pat::PFILLED, apt_size::SH); \
    TEST_BIN_OP(sfx##_fdo, op, sgnd, oc, lsgn, lp, ls, rsgn, apt_pat::PFILLED, apt_size::SO); \
    TEST_BIN_OP(sfx##_c0f, op, sgnd, oc, lsgn, lp, ls, rsgn, apt_pat::PCHESS0, apt_size::SF); \
    TEST_BIN_OP(sfx##_c0h, op, sgnd, oc, lsgn, lp, ls, rsgn, apt_pat::PCHESS0, apt_size::SH); \
    TEST_BIN_OP(sfx##_c0o, op, sgnd, oc, lsgn, lp, ls, rsgn, apt_pat::PCHESS0, apt_size::SO); \
    TEST_BIN_OP(sfx##_c1f, op, sgnd, oc, lsgn, lp, ls, rsgn, apt_pat::PCHESS1, apt_size::SF); \
    TEST_BIN_OP(sfx##_c1h, op, sgnd, oc, lsgn, lp, ls, rsgn, apt_pat::PCHESS1, apt_size::SH); \
    TEST_BIN_OP(sfx##_c1o, op, sgnd, oc, lsgn, lp, ls, rsgn, apt_pat::PCHESS1, apt_size::SO); \
    TEST_BIN_OP(sfx##_mhf, op, sgnd, oc, lsgn, lp, ls, rsgn, apt_pat::PMISSHB, apt_size::SF); \
    TEST_BIN_OP(sfx##_mlf, op, sgnd, oc, lsgn, lp, ls, rsgn, apt_pat::PMISSLB, apt_size::SF); \
    TEST_BIN_OP(sfx##_ohf, op, sgnd, oc, lsgn, lp, ls, rsgn, apt_pat::PONLYHB, apt_size::SF); \
    TEST_BIN_OP(sfx##_olo, op, sgnd, oc, lsgn, lp, ls, rsgn, apt_pat::PONLYLB, apt_size::SO); \
    TEST_BIN_OP(sfx##_zdz, op, sgnd, oc, lsgn, lp, ls, rsgn, apt_pat::PZEROED, apt_size::SZ)

// Suite, only capacity and signs of left and right operands can be set.
// suffix
// operation
// signedness of the operation
// out capacity
// left sign
// right sign
#define TEST_BIN_OP_SUITE(sfx, op, sgnd, oc, lsgn, rsgn)                                                  \
    TEST_BIN_OP_SUITE_STEP(sgnd##_##sfx##_fdf, op, sgnd, oc, lsgn, apt_pat::PFILLED, apt_size::SF, rsgn); \
    TEST_BIN_OP_SUITE_STEP(sgnd##_##sfx##_fdh, op, sgnd, oc, lsgn, apt_pat::PFILLED, apt_size::SH, rsgn); \
    TEST_BIN_OP_SUITE_STEP(sgnd##_##sfx##_fdo, op, sgnd, oc, lsgn, apt_pat::PFILLED, apt_size::SO, rsgn); \
    TEST_BIN_OP_SUITE_STEP(sgnd##_##sfx##_c0f, op, sgnd, oc, lsgn, apt_pat::PCHESS0, apt_size::SF, rsgn); \
    TEST_BIN_OP_SUITE_STEP(sgnd##_##sfx##_c0h, op, sgnd, oc, lsgn, apt_pat::PCHESS0, apt_size::SH, rsgn); \
    TEST_BIN_OP_SUITE_STEP(sgnd##_##sfx##_c0o, op, sgnd, oc, lsgn, apt_pat::PCHESS0, apt_size::SO, rsgn); \
    TEST_BIN_OP_SUITE_STEP(sgnd##_##sfx##_c1f, op, sgnd, oc, lsgn, apt_pat::PCHESS1, apt_size::SF, rsgn); \
    TEST_BIN_OP_SUITE_STEP(sgnd##_##sfx##_c1h, op, sgnd, oc, lsgn, apt_pat::PCHESS1, apt_size::SH, rsgn); \
    TEST_BIN_OP_SUITE_STEP(sgnd##_##sfx##_c1o, op, sgnd, oc, lsgn, apt_pat::PCHESS1, apt_size::SO, rsgn); \
    TEST_BIN_OP_SUITE_STEP(sgnd##_##sfx##_mhf, op, sgnd, oc, lsgn, apt_pat::PMISSHB, apt_size::SF, rsgn); \
    TEST_BIN_OP_SUITE_STEP(sgnd##_##sfx##_mlf, op, sgnd, oc, lsgn, apt_pat::PMISSLB, apt_size::SF, rsgn); \
    TEST_BIN_OP_SUITE_STEP(sgnd##_##sfx##_ohf, op, sgnd, oc, lsgn, apt_pat::PONLYHB, apt_size::SF, rsgn); \
    TEST_BIN_OP_SUITE_STEP(sgnd##_##sfx##_olo, op, sgnd, oc, lsgn, apt_pat::PONLYLB, apt_size::SO, rsgn); \
    TEST_BIN_OP_SUITE_STEP(sgnd##_##sfx##_zdz, op, sgnd, oc, lsgn, apt_pat::PZEROED, apt_size::SZ, AP_N)

// Test case, both parameters can be configured.
// suffix
// operation
// signedness of the operation
// out capacity
// in sign
// in pattern
// in size
#define TEST_UN_OP(sfx, op, sgnd, oc, isgn, ip, is)                                   \
    TEST(xapi_##op, sfx)                                                              \
    {                                                                                 \
        std::string istr = apt_strp(ip, apt_cap::CMAX, is, isgn);                     \
        std::string estr = apt_str##sgnd(bapi_##op##_##sgnd(istr), oc, apt_size::SF); \
        std::string ostr = xapi_##op##_##sgnd(istr, oc);                              \
        ASSERT_EQ(ostr, estr);                                                        \
    }

// Suite, only capacity and signs of left and right operands can be set.
// suffix
// operation
// signedness of the operation
// out capacity
// left sign
// right sign
#define TEST_UN_OP_SUITE(sfx, op, sgnd, oc, isgn)                                       \
    TEST_UN_OP(sgnd##_##sfx##_fdf, op, sgnd, oc, isgn, apt_pat::PFILLED, apt_size::SF); \
    TEST_UN_OP(sgnd##_##sfx##_fdh, op, sgnd, oc, isgn, apt_pat::PFILLED, apt_size::SH); \
    TEST_UN_OP(sgnd##_##sfx##_fdo, op, sgnd, oc, isgn, apt_pat::PFILLED, apt_size::SO); \
    TEST_UN_OP(sgnd##_##sfx##_c0f, op, sgnd, oc, isgn, apt_pat::PCHESS0, apt_size::SF); \
    TEST_UN_OP(sgnd##_##sfx##_c0h, op, sgnd, oc, isgn, apt_pat::PCHESS0, apt_size::SH); \
    TEST_UN_OP(sgnd##_##sfx##_c0o, op, sgnd, oc, isgn, apt_pat::PCHESS0, apt_size::SO); \
    TEST_UN_OP(sgnd##_##sfx##_c1f, op, sgnd, oc, isgn, apt_pat::PCHESS1, apt_size::SF); \
    TEST_UN_OP(sgnd##_##sfx##_c1h, op, sgnd, oc, isgn, apt_pat::PCHESS1, apt_size::SH); \
    TEST_UN_OP(sgnd##_##sfx##_c1o, op, sgnd, oc, isgn, apt_pat::PCHESS1, apt_size::SO); \
    TEST_UN_OP(sgnd##_##sfx##_mhf, op, sgnd, oc, isgn, apt_pat::PMISSHB, apt_size::SF); \
    TEST_UN_OP(sgnd##_##sfx##_mlf, op, sgnd, oc, isgn, apt_pat::PMISSLB, apt_size::SF); \
    TEST_UN_OP(sgnd##_##sfx##_ohf, op, sgnd, oc, isgn, apt_pat::PONLYHB, apt_size::SF); \
    TEST_UN_OP(sgnd##_##sfx##_olo, op, sgnd, oc, isgn, apt_pat::PONLYLB, apt_size::SO); \
    TEST_UN_OP(sgnd##_##sfx##_zdz, op, sgnd, oc, isgn, apt_pat::PZEROED, apt_size::SZ)

#endif
