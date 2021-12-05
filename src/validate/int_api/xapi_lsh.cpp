#include "../common.hpp"

static inline index_t toshift(const std::string& str)
{
    static const index_t numchars = sizeof(index_t) * 2;
    if (str.size() > numchars + 2)
    {
        return index_t(-1);
    }
    return std::stoull(str, nullptr, 16);
}

static inline std::string bapi_lsh_u(const std::string& lstr, const std::string& rstr)
{
    boost_uint lv;
    index_t rv = toshift(rstr);
    lv.assign(lstr);
    boost_uint ov = lv << rv;
    return std::string("0x") + ov.str(0, std::ios_base::hex);
}

static inline std::string bapi_lsh_s(const std::string& lstr, const std::string& rstr)
{
    boost_int lv;
    index_t rv = toshift(rstr);
    lv.assign(apt_strs(lstr, apt_cap::CMAX, apt_size::SF));
    boost_uint ov;
    ov.assign(lv << rv);
    return std::string("0x") + ov.str(0, std::ios_base::hex);
}

static inline std::string xapi_lsh_u(const std::string& lstr, const std::string& rstr, apt_cap c)
{
    std::string result;
    AP_REGISTER(l, apt_gcapw(apt_cap::CMAX), 0, false);
    index_t r = toshift(rstr);
    AP_REGISTER(o, apt_gcapw(c), 0, false);
    uapi_fstr(l, lstr.c_str(), lstr.size(), 16, "0123456789ABCDEF");
    uapi_lsh(rregister(l), r, o);
    uapi_tstr(rregister(o), result, 16, "0123456789ABCDEF");
    return result;
}

static inline std::string xapi_lsh_s(const std::string& lstr, const std::string& rstr, apt_cap c)
{
    std::string result;
    AP_REGISTER(l, apt_gcapw(apt_cap::CMAX), 0, false);
    index_t r = toshift(rstr);
    AP_REGISTER(o, apt_gcapw(c), 0, false);
    sapi_fstr(l, lstr.c_str(), lstr.size(), 16, "0123456789ABCDEF");
    sapi_lsh(rregister(l), r, o);
    sapi_tstr(rregister(o), result, 16, "0123456789ABCDEF");
    return result;
}

TEST(xapi_lsh, build)
{
    AP_REGISTER(l, apt_gcap(apt_cap::CMAX), 0, false);
    index_t r = 1;
    AP_REGISTER(o, apt_gcap(apt_cap::CMAX), 0, false);
    uapi_lsh(rregister(l), r, o);
    sapi_lsh(rregister(l), r, o);
}

TEST_BIN_OP_SUITE(mxuu, lsh, u, apt_cap::CMAX, AP_P, AP_P);
TEST_BIN_OP_SUITE(mduu, lsh, u, apt_cap::CMID, AP_P, AP_P);
TEST_BIN_OP_SUITE(mnuu, lsh, u, apt_cap::CMIN, AP_P, AP_P);
TEST_BIN_OP_SUITE(mxuu, lsh, s, apt_cap::CMAX, AP_P, AP_P);
TEST_BIN_OP_SUITE(mduu, lsh, s, apt_cap::CMID, AP_P, AP_P);
TEST_BIN_OP_SUITE(mnuu, lsh, s, apt_cap::CMIN, AP_P, AP_P);
TEST_BIN_OP_SUITE(mxus, lsh, s, apt_cap::CMAX, AP_P, AP_N);
TEST_BIN_OP_SUITE(mdus, lsh, s, apt_cap::CMID, AP_P, AP_N);
TEST_BIN_OP_SUITE(mnus, lsh, s, apt_cap::CMIN, AP_P, AP_N);
TEST_BIN_OP_SUITE(mxsu, lsh, s, apt_cap::CMAX, AP_N, AP_P);
TEST_BIN_OP_SUITE(mdsu, lsh, s, apt_cap::CMID, AP_N, AP_P);
TEST_BIN_OP_SUITE(mnsu, lsh, s, apt_cap::CMIN, AP_N, AP_P);
TEST_BIN_OP_SUITE(mxss, lsh, s, apt_cap::CMAX, AP_N, AP_N);
TEST_BIN_OP_SUITE(mdss, lsh, s, apt_cap::CMID, AP_N, AP_N);
TEST_BIN_OP_SUITE(mnss, lsh, s, apt_cap::CMIN, AP_N, AP_N);
