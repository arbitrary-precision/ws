#include "../common.hpp"

static inline std::string bapi_tou_u(const std::string& istr)
{
    boost_uint v;
    v.assign(istr);
    return std::string("0x") + v.str(0, std::ios_base::hex);
}

static inline std::string bapi_tou_s(const std::string& istr)
{
    return bapi_tou_u(istr);
}

static inline std::string xapi_tou_u(const std::string& istr, apt_cap c)
{
    throw std::runtime_error{"xapi_tou_s not implemented."};
}

static inline std::string xapi_tou_s(const std::string& istr, apt_cap c)
{
    std::string result;
    AP_REGISTER(i, apt_gcapw(apt_cap::CMAX), 0, false);
    AP_REGISTER(o, apt_gcapw(c), 0, false);
    sapi_fstr(i, istr.c_str(), istr.size(), 16, "0123456789ABCDEF");
    sapi_tou(rregister(i), o);
    uapi_tstr(rregister(o), result, 16, "0123456789ABCDEF");
    return apt_strs(result, c, apt_size::SF);
}

TEST(xapi_tou, build)
{
    AP_REGISTER(i, 1, 0, false);
    AP_REGISTER(o, 1, 0, false);
    sapi_tou(rregister(i), o);
}

TEST_UN_OP_SUITE(mxu, tou, s, apt_cap::CMAX, AP_P);
TEST_UN_OP_SUITE(mdu, tou, s, apt_cap::CMID, AP_P);
TEST_UN_OP_SUITE(mnu, tou, s, apt_cap::CMIN, AP_P);
TEST_UN_OP_SUITE(mxs, tou, s, apt_cap::CMAX, AP_N);
TEST_UN_OP_SUITE(mds, tou, s, apt_cap::CMID, AP_N);
TEST_UN_OP_SUITE(mns, tou, s, apt_cap::CMIN, AP_N);
