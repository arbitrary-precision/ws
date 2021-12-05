
#include "../common.hpp"
#include <algorithm>

#define AP_CUSTOM_DIGITS "0123456789ABCDEF"

// Automatic detection of base
#define ta 0
// Known base 2
#define tb 2
// Known base 8
#define to 8
// Known base 10
#define td 10
// Known base 16
#define tx 16

static inline std::string str_prefix(index_t b)
{
    static const std::string prefixes[4] =
        {
            "0b",
            "0",
            "",
            "0x"};
    return prefixes[b];
}

// base 2
#define BASEB 0
// base 8
#define BASEO 1
// base 10
#define BASED 2
// base 16
#define BASEX 3

// z - [AP_WZEROED, AP_WZEROED, AP_WZEROED] - zero
#define NCASE0 0
// o - [AP_WONLYLB, AP_WZEROED, AP_WZEROED] - one
#define NCASE1 1
// v - [AP_WFILLED, AP_WZEROED, AP_WFILLED] - wrapping with trim (vanish)
#define NCASEV 2
// w - [AP_WFILLED, AP_WONLYLB, AP_WFILLED] - wrapping
#define NCASEW 3
// f - [AP_WFILLED, AP_WFILLED, AP_WFILLED] - wrapping filled
#define NCASEF 4

static inline std::string str_specific(index_t b, index_t c)
{
    // 4 cases, 4 bases, 3 word sizes
    static const std::string cases[4][4][5] =
        {
            // base 2
            {
                // word size 1
                {
                    "0",
                    "1",
                    "11111111"
                    "00000000"
                    "11111111",
                    "11111111"
                    "00000001"
                    "11111111",
                    "11111111"
                    "11111111"
                    "11111111",
                },
                // word size 2
                {
                    "0",
                    "1",
                    "1111111111111111"
                    "0000000000000000"
                    "1111111111111111",
                    "1111111111111111"
                    "0000000000000001"
                    "1111111111111111",
                    "1111111111111111"
                    "1111111111111111"
                    "1111111111111111",
                },
                // word size 3 not checked
                {},
                // word size 4
                {
                    "0",
                    "1",
                    "11111111111111111111111111111111"
                    "00000000000000000000000000000000"
                    "11111111111111111111111111111111",
                    "11111111111111111111111111111111"
                    "00000000000000000000000000000001"
                    "11111111111111111111111111111111",
                    "11111111111111111111111111111111"
                    "11111111111111111111111111111111"
                    "11111111111111111111111111111111"}},
            // base 8
            {
                // word size 1
                {
                    "0",
                    "1",
                    "77600377",
                    "77600777",
                    "77777777"},
                // word size 2
                {
                    "0",
                    "1",
                    "7777740000177777",
                    "7777740000377777",
                    "7777777777777777"},
                // word size 3 not checked
                {},
                // word size 4
                {
                    "0",
                    "1",
                    "77777777776000000000037777777777",
                    "77777777776000000000077777777777",
                    "77777777777777777777777777777777"}},
            // base 10
            {
                // word size 1
                {
                    "0",
                    "1",
                    "16711935",
                    "16712191",
                    "16777215"},
                // word size 2
                {
                    "0",
                    "1",
                    "281470681808895",
                    "281470681874431",
                    "281474976710655"},
                // word size 3 not checked
                {},
                // word size 4
                {
                    "0",
                    "1",
                    "79228162495817593524129366015",
                    "79228162495817593528424333311",
                    "79228162514264337593543950335"}},
            // base 16
            {
                // word size 1
                {
                    "0",
                    "1",
                    "FF"
                    "00"
                    "FF",
                    "FF"
                    "01"
                    "FF",
                    "FF"
                    "FF"
                    "FF"},
                // word size 2
                {
                    "0",
                    "1",
                    "FFFF"
                    "0000"
                    "FFFF",
                    "FFFF"
                    "0001"
                    "FFFF",
                    "FFFF"
                    "FFFF"
                    "FFFF"},
                // word size 3 not checked
                {},
                // word size 4
                {
                    "0",
                    "1",
                    "FFFFFFFF"
                    "00000000"
                    "FFFFFFFF",
                    "FFFFFFFF"
                    "00000001"
                    "FFFFFFFF",
                    "FFFFFFFF"
                    "FFFFFFFF"
                    "FFFFFFFF"}}};
    return cases[b][sizeof(word_t) - 1][c];
}

static inline std::string str_trail(index_t b, index_t c)
{
    return std::string("000000000000") + str_specific(b, c);
}

// Here case is either 0 or 1.
static inline std::string str_broken(index_t b, index_t c)
{
    static const std::string cases[2][4] =
        {
            {
                "1111211111111111111111111",
                "178213131321312313231313131",
                "15A2342834892343247824938492",
                "FG2342834892343247824938492",
            },
            {
                "1111#11111111111111111111",
                "17#213131321312313231313131",
                "15#2342834892343247824938492",
                "F#2342834892343247824938492",
            }};
    return cases[c][b];
}

// sgn - either u or s - signedness
// sfx - custom suffix
// b - base detection (ta, tb, to, td, tx)
// s - string
// es - expected sign (AP_P, AP_N)
// el - expected size
// ... - expected words
#define TEST_FSTR(sgn, sfx, b, d, s, es, el, ...)              \
    TEST(xapi_fstt, tu_##sgn##int_fstr_##sfx##_##b)            \
    {                                                          \
        std::string str = s;                                   \
        AP_REGISTER(out, 2, 2, false, AP_WHEPROT, AP_WHEPROT); \
        AP_REGISTER(exp, 2, el, es, __VA_ARGS__);              \
        sgn##api_fstr(out, s.c_str(), s.size(), b, d);         \
        AP_ASSERT_REG(out, exp);                               \
    }

TEST(xapi_fstr, build)
{
    AP_REGISTER(o, 1, 0, false);
    uapi_fstr(o, "1", 1, 1, AP_CUSTOM_DIGITS);
    sapi_fstr(o, "1", 1, 1, AP_CUSTOM_DIGITS);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Unsigned.

// n - normal case
TEST_FSTR(u, nzb, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_specific(BASEB, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, nob, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_specific(BASEB, NCASE1)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, nwb, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_specific(BASEB, NCASEV)), false, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(u, nvb, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_specific(BASEB, NCASEW)), false, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(u, nfb, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_specific(BASEB, NCASEF)), false, 2, AP_WFILLED, AP_WFILLED);
TEST_FSTR(u, nzo, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_specific(BASEO, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, noo, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_specific(BASEO, NCASE1)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, nwo, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_specific(BASEO, NCASEV)), false, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(u, nvo, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_specific(BASEO, NCASEW)), false, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(u, nfo, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_specific(BASEO, NCASEF)), false, 2, AP_WFILLED, AP_WFILLED);
TEST_FSTR(u, nzd, ta, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_specific(BASED, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, nod, ta, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_specific(BASED, NCASE1)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, nwd, ta, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_specific(BASED, NCASEV)), false, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(u, nvd, ta, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_specific(BASED, NCASEW)), false, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(u, nfd, ta, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_specific(BASED, NCASEF)), false, 2, AP_WFILLED, AP_WFILLED);
TEST_FSTR(u, nzx, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, nox, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASE1)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, nwx, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASEV)), false, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(u, nvx, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASEW)), false, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(u, nfx, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASEF)), false, 2, AP_WFILLED, AP_WFILLED);
TEST_FSTR(u, nzs, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, nos, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASE1)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, nws, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASEV)), false, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(u, nvs, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASEW)), false, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(u, nfs, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASEF)), false, 2, AP_WFILLED, AP_WFILLED);

// u - normal case with +
TEST_FSTR(u, uzb, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEB) + str_specific(BASEB, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, uob, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEB) + str_specific(BASEB, NCASE1)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, uwb, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEB) + str_specific(BASEB, NCASEV)), false, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(u, uvb, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEB) + str_specific(BASEB, NCASEW)), false, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(u, ufb, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEB) + str_specific(BASEB, NCASEF)), false, 2, AP_WFILLED, AP_WFILLED);
TEST_FSTR(u, uzo, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEO) + str_specific(BASEO, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, uoo, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEO) + str_specific(BASEO, NCASE1)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, uwo, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEO) + str_specific(BASEO, NCASEV)), false, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(u, uvo, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEO) + str_specific(BASEO, NCASEW)), false, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(u, ufo, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEO) + str_specific(BASEO, NCASEF)), false, 2, AP_WFILLED, AP_WFILLED);
TEST_FSTR(u, uzd, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASED) + str_specific(BASED, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, uod, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASED) + str_specific(BASED, NCASE1)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, uwd, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASED) + str_specific(BASED, NCASEV)), false, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(u, uvd, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASED) + str_specific(BASED, NCASEW)), false, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(u, ufd, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASED) + str_specific(BASED, NCASEF)), false, 2, AP_WFILLED, AP_WFILLED);
TEST_FSTR(u, uzx, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, uox, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASE1)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, uwx, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASEV)), false, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(u, uvx, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASEW)), false, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(u, ufx, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASEF)), false, 2, AP_WFILLED, AP_WFILLED);
TEST_FSTR(u, uzs, tx, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, uos, tx, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASE1)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, uws, tx, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASEV)), false, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(u, uvs, tx, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASEW)), false, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(u, ufs, tx, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASEF)), false, 2, AP_WFILLED, AP_WFILLED);

// s - normal case with -
TEST_FSTR(u, szb, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEB) + str_specific(BASEB, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, sob, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEB) + str_specific(BASEB, NCASE1)), false, 2, AP_WFILLED, AP_WFILLED);
TEST_FSTR(u, swb, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEB) + str_specific(BASEB, NCASEV)), false, 2, AP_WONLYLB, AP_WFILLED);
TEST_FSTR(u, svb, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEB) + str_specific(BASEB, NCASEW)), false, 2, AP_WONLYLB, AP_WMISSLB);
TEST_FSTR(u, sfb, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEB) + str_specific(BASEB, NCASEF)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, szo, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEO) + str_specific(BASEO, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, soo, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEO) + str_specific(BASEO, NCASE1)), false, 2, AP_WFILLED, AP_WFILLED);
TEST_FSTR(u, swo, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEO) + str_specific(BASEO, NCASEV)), false, 2, AP_WONLYLB, AP_WFILLED);
TEST_FSTR(u, svo, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEO) + str_specific(BASEO, NCASEW)), false, 2, AP_WONLYLB, AP_WMISSLB);
TEST_FSTR(u, sfo, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEO) + str_specific(BASEO, NCASEF)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, szd, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASED) + str_specific(BASED, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, sod, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASED) + str_specific(BASED, NCASE1)), false, 2, AP_WFILLED, AP_WFILLED);
TEST_FSTR(u, swd, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASED) + str_specific(BASED, NCASEV)), false, 2, AP_WONLYLB, AP_WFILLED);
TEST_FSTR(u, svd, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASED) + str_specific(BASED, NCASEW)), false, 2, AP_WONLYLB, AP_WMISSLB);
TEST_FSTR(u, sfd, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASED) + str_specific(BASED, NCASEF)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, szx, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, sox, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASE1)), false, 2, AP_WFILLED, AP_WFILLED);
TEST_FSTR(u, swx, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASEV)), false, 2, AP_WONLYLB, AP_WFILLED);
TEST_FSTR(u, svx, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASEW)), false, 2, AP_WONLYLB, AP_WMISSLB);
TEST_FSTR(u, sfx, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASEF)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, szs, tx, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, sos, tx, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASE1)), false, 2, AP_WFILLED, AP_WFILLED);
TEST_FSTR(u, sws, tx, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASEV)), false, 2, AP_WONLYLB, AP_WFILLED);
TEST_FSTR(u, svs, tx, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASEW)), false, 2, AP_WONLYLB, AP_WMISSLB);
TEST_FSTR(u, sfs, tx, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASEF)), false, 1, AP_WONLYLB, AP_WZEROED);

// t  - Trailing zeros.
TEST_FSTR(u, tzb, tb, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_trail(BASEB, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, tob, tb, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_trail(BASEB, NCASE1)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, twb, tb, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_trail(BASEB, NCASEV)), false, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(u, tvb, tb, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_trail(BASEB, NCASEW)), false, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(u, tfs, tb, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_trail(BASEB, NCASEF)), false, 2, AP_WFILLED, AP_WFILLED);
TEST_FSTR(u, tzo, to, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_trail(BASEO, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, too, to, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_trail(BASEO, NCASE1)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, two, to, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_trail(BASEO, NCASEV)), false, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(u, tvo, to, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_trail(BASEO, NCASEW)), false, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(u, tfs, to, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_trail(BASEO, NCASEF)), false, 2, AP_WFILLED, AP_WFILLED);
TEST_FSTR(u, tzd, td, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_trail(BASED, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, tod, td, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_trail(BASED, NCASE1)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, twd, td, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_trail(BASED, NCASEV)), false, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(u, tvd, td, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_trail(BASED, NCASEW)), false, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(u, tfs, td, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_trail(BASED, NCASEF)), false, 2, AP_WFILLED, AP_WFILLED);
TEST_FSTR(u, tzs, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_trail(BASEX, NCASE0)), false, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(u, tos, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_trail(BASEX, NCASE1)), false, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(u, tws, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_trail(BASEX, NCASEV)), false, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(u, tvs, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_trail(BASEX, NCASEW)), false, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(u, tfs, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_trail(BASEX, NCASEF)), false, 2, AP_WFILLED, AP_WFILLED);

// b - Invalid character for base.
TEST_FSTR(u, b, tb, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_broken(BASEB, 0)), false, 1, 15);
TEST_FSTR(u, b, to, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_broken(BASEO, 0)), false, 1, 15);
TEST_FSTR(u, b, td, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_broken(BASED, 0)), false, 1, 15);
TEST_FSTR(u, b, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_broken(BASEX, 0)), false, 1, 15);

// g - Invalid character in general.
TEST_FSTR(u, g, tb, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_broken(BASEB, 1)), false, 1, 15);
TEST_FSTR(u, g, to, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_broken(BASEO, 1)), false, 1, 15);
TEST_FSTR(u, g, td, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_broken(BASED, 1)), false, 1, 15);
TEST_FSTR(u, g, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_broken(BASEX, 1)), false, 1, 15);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Signed.

// n - normal case
TEST_FSTR(s, nzb, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_specific(BASEB, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, nob, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_specific(BASEB, NCASE1)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, nwb, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_specific(BASEB, NCASEV)), AP_P, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, nvb, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_specific(BASEB, NCASEW)), AP_P, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, nfb, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_specific(BASEB, NCASEF)), AP_N, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, nzo, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_specific(BASEO, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, noo, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_specific(BASEO, NCASE1)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, nwo, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_specific(BASEO, NCASEV)), AP_P, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, nvo, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_specific(BASEO, NCASEW)), AP_P, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, nfo, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_specific(BASEO, NCASEF)), AP_N, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, nzd, ta, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_specific(BASED, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, nod, ta, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_specific(BASED, NCASE1)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, nwd, ta, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_specific(BASED, NCASEV)), AP_P, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, nvd, ta, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_specific(BASED, NCASEW)), AP_P, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, nfd, ta, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_specific(BASED, NCASEF)), AP_N, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, nzx, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, nox, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASE1)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, nwx, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASEV)), AP_P, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, nvx, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASEW)), AP_P, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, nfx, ta, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASEF)), AP_N, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, nzs, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, nos, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASE1)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, nws, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASEV)), AP_P, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, nvs, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASEW)), AP_P, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, nfs, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_specific(BASEX, NCASEF)), AP_N, 1, AP_WONLYLB, AP_WZEROED);

// u - normal case with +
TEST_FSTR(s, uzb, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEB) + str_specific(BASEB, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, uob, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEB) + str_specific(BASEB, NCASE1)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, uwb, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEB) + str_specific(BASEB, NCASEV)), AP_P, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, uvb, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEB) + str_specific(BASEB, NCASEW)), AP_P, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, ufb, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEB) + str_specific(BASEB, NCASEF)), AP_N, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, uzo, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEO) + str_specific(BASEO, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, uoo, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEO) + str_specific(BASEO, NCASE1)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, uwo, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEO) + str_specific(BASEO, NCASEV)), AP_P, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, uvo, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEO) + str_specific(BASEO, NCASEW)), AP_P, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, ufo, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEO) + str_specific(BASEO, NCASEF)), AP_N, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, uzd, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASED) + str_specific(BASED, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, uod, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASED) + str_specific(BASED, NCASE1)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, uwd, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASED) + str_specific(BASED, NCASEV)), AP_P, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, uvd, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASED) + str_specific(BASED, NCASEW)), AP_P, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, ufd, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASED) + str_specific(BASED, NCASEF)), AP_N, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, uzx, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, uox, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASE1)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, uwx, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASEV)), AP_P, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, uvx, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASEW)), AP_P, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, ufx, ta, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASEF)), AP_N, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, uzs, tx, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, uos, tx, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASE1)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, uws, tx, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASEV)), AP_P, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, uvs, tx, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASEW)), AP_P, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, ufs, tx, AP_CUSTOM_DIGITS, (std::string("+") + str_prefix(BASEX) + str_specific(BASEX, NCASEF)), AP_N, 1, AP_WONLYLB, AP_WZEROED);

// s - normal case with -
TEST_FSTR(s, szb, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEB) + str_specific(BASEB, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, sob, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEB) + str_specific(BASEB, NCASE1)), AP_N, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, swb, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEB) + str_specific(BASEB, NCASEV)), AP_N, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, svb, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEB) + str_specific(BASEB, NCASEW)), AP_N, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, sfb, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEB) + str_specific(BASEB, NCASEF)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, szo, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEO) + str_specific(BASEO, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, soo, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEO) + str_specific(BASEO, NCASE1)), AP_N, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, swo, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEO) + str_specific(BASEO, NCASEV)), AP_N, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, svo, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEO) + str_specific(BASEO, NCASEW)), AP_N, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, sfo, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEO) + str_specific(BASEO, NCASEF)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, szd, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASED) + str_specific(BASED, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, sod, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASED) + str_specific(BASED, NCASE1)), AP_N, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, swd, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASED) + str_specific(BASED, NCASEV)), AP_N, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, svd, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASED) + str_specific(BASED, NCASEW)), AP_N, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, sfd, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASED) + str_specific(BASED, NCASEF)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, szx, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, sox, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASE1)), AP_N, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, swx, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASEV)), AP_N, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, svx, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASEW)), AP_N, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, sfx, ta, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASEF)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, szs, tx, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, sos, tx, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASE1)), AP_N, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, sws, tx, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASEV)), AP_N, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, svs, tx, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASEW)), AP_N, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, sfs, tx, AP_CUSTOM_DIGITS, (std::string("-") + str_prefix(BASEX) + str_specific(BASEX, NCASEF)), AP_P, 1, AP_WONLYLB, AP_WZEROED);

// t  - Trailing zeros.
TEST_FSTR(s, tzb, tb, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_trail(BASEB, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, tob, tb, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_trail(BASEB, NCASE1)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, twb, tb, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_trail(BASEB, NCASEV)), AP_P, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, tvb, tb, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_trail(BASEB, NCASEW)), AP_P, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, tfb, tb, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_trail(BASEB, NCASEF)), AP_N, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, tzo, to, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_trail(BASEO, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, too, to, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_trail(BASEO, NCASE1)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, two, to, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_trail(BASEO, NCASEV)), AP_P, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, tvo, to, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_trail(BASEO, NCASEW)), AP_P, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, tfo, to, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_trail(BASEO, NCASEF)), AP_N, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, tzd, td, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_trail(BASED, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, tod, td, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_trail(BASED, NCASE1)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, twd, td, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_trail(BASED, NCASEV)), AP_P, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, tvd, td, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_trail(BASED, NCASEW)), AP_P, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, tfd, td, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_trail(BASED, NCASEF)), AP_N, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, tzx, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_trail(BASEX, NCASE0)), AP_P, 0, AP_WZEROED, AP_WZEROED);
TEST_FSTR(s, tox, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_trail(BASEX, NCASE1)), AP_P, 1, AP_WONLYLB, AP_WZEROED);
TEST_FSTR(s, twx, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_trail(BASEX, NCASEV)), AP_P, 1, AP_WFILLED, AP_WZEROED);
TEST_FSTR(s, tvx, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_trail(BASEX, NCASEW)), AP_P, 2, AP_WFILLED, AP_WONLYLB);
TEST_FSTR(s, tfx, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_trail(BASEX, NCASEF)), AP_N, 1, AP_WONLYLB, AP_WZEROED);

// b - Invalid character for base.
TEST_FSTR(s, b, tb, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_broken(BASEB, 0)), false, 1, 15);
TEST_FSTR(s, b, to, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_broken(BASEO, 0)), false, 1, 15);
TEST_FSTR(s, b, td, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_broken(BASED, 0)), false, 1, 15);
TEST_FSTR(s, b, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_broken(BASEX, 0)), false, 1, 15);

// g - Invalid character in general.
TEST_FSTR(s, g, tb, AP_CUSTOM_DIGITS, (str_prefix(BASEB) + str_broken(BASEB, 1)), false, 1, 15);
TEST_FSTR(s, g, to, AP_CUSTOM_DIGITS, (str_prefix(BASEO) + str_broken(BASEO, 1)), false, 1, 15);
TEST_FSTR(s, g, td, AP_CUSTOM_DIGITS, (str_prefix(BASED) + str_broken(BASED, 1)), false, 1, 15);
TEST_FSTR(s, g, tx, AP_CUSTOM_DIGITS, (str_prefix(BASEX) + str_broken(BASEX, 1)), false, 1, 15);
