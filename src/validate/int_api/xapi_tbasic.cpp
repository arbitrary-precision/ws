#include "../common.hpp"

static inline std::string tohex(unsigned long long a)
{
    char buff[50];
    sprintf(buff, "0x%llX", a);
    return std::string(buff);
}

static inline std::string bapi_tbasic_u(const std::string& istr)
{
    boost_uint v;
    v.assign(istr);
    return tohex(static_cast<unsigned long long>(v));
}

static inline std::string bapi_tbasic_s(const std::string& istr)
{
    return bapi_tbasic_u(istr);
}

static inline std::string xapi_tbasic_u(const std::string& istr, apt_cap c)
{
    AP_REGISTER(i, apt_gcapw(c), 0, false);
    uapi_fstr(i, istr.c_str(), istr.size(), 16, "0123456789ABCDEF");
    return tohex(uapi_tbasic(rregister(i)));
}

static inline std::string xapi_tbasic_s(const std::string& istr, apt_cap c)
{
    AP_REGISTER(i, apt_gcapw(c), 0, false);
    sapi_fstr(i, istr.c_str(), istr.size(), 16, "0123456789ABCDEF");
    return apt_strs(tohex(sapi_tbasic(rregister(i))), c, apt_size::SF);
}

TEST(xapi_tbasic, build)
{
    AP_REGISTER(i, 1, 0, false);
    uapi_tbasic(rregister(i));
    sapi_tbasic(rregister(i));
}

TEST_UN_OP_SUITE(mxu, tbasic, u, apt_cap::CMAX, AP_P);
TEST_UN_OP_SUITE(mdu, tbasic, u, apt_cap::CMID, AP_P);
TEST_UN_OP_SUITE(mnu, tbasic, u, apt_cap::CMIN, AP_P);
TEST_UN_OP_SUITE(mxu, tbasic, s, apt_cap::CMAX, AP_P);
TEST_UN_OP_SUITE(mdu, tbasic, s, apt_cap::CMID, AP_P);
TEST_UN_OP_SUITE(mnu, tbasic, s, apt_cap::CMIN, AP_P);
TEST_UN_OP_SUITE(mxs, tbasic, s, apt_cap::CMAX, AP_N);
TEST_UN_OP_SUITE(mds, tbasic, s, apt_cap::CMID, AP_N);
TEST_UN_OP_SUITE(mns, tbasic, s, apt_cap::CMIN, AP_N);
