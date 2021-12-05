#include "../common.hpp"

static inline std::string cut_to_fit(std::string str)
{
    if ((sizeof(unsigned long long) * 2) < (str.size() - 2))
    {
        return std::string("0x") + str.substr(str.size() - sizeof(unsigned long long) * 2);
    }
    else
    {
        return str;
    }
}

static inline std::string bapi_fbasic_u(const std::string& istr)
{
    boost_uint v;
    v.assign(std::stoull(cut_to_fit(istr), nullptr, 16));
    boost_uint ov = v;
    return std::string("0x") + ov.str(0, std::ios_base::hex);
}

static inline std::string bapi_fbasic_s(const std::string& istr)
{
    boost_uint v;
    v.assign(static_cast<signed long long>(std::stoull(cut_to_fit(istr), nullptr, 16)));
    boost_uint ov = v;
    return std::string("0x") + ov.str(0, std::ios_base::hex);
}

static inline std::string xapi_fbasic_u(const std::string& istr, apt_cap c)
{
    std::string result;
    AP_REGISTER(o, apt_gcapw(c), 0, false);
    unsigned long long v = std::stoull(cut_to_fit(istr), nullptr, 16);
    uapi_fbasic(o, v);
    uapi_tstr(rregister(o), result, 16, "0123456789ABCDEF");
    return result;
}

static inline std::string xapi_fbasic_s(const std::string& istr, apt_cap c)
{
    std::string result;
    AP_REGISTER(o, apt_gcapw(c), 0, false);
    long long v = std::stoull(cut_to_fit(istr), nullptr, 16);
    sapi_fbasic(o, v);
    sapi_tstr(rregister(o), result, 16, "0123456789ABCDEF");
    return result;
}

TEST(xapi_fbasic, build)
{
    AP_REGISTER(o, 1, 0, false);
    uapi_fbasic(o, 1);
    sapi_fbasic(o, 1);
}

TEST_UN_OP_SUITE(mxu, fbasic, u, apt_cap::CMAX, AP_P);
TEST_UN_OP_SUITE(mdu, fbasic, u, apt_cap::CMID, AP_P);
TEST_UN_OP_SUITE(mnu, fbasic, u, apt_cap::CMIN, AP_P);
TEST_UN_OP_SUITE(mxu, fbasic, s, apt_cap::CMAX, AP_P);
TEST_UN_OP_SUITE(mdu, fbasic, s, apt_cap::CMID, AP_P);
TEST_UN_OP_SUITE(mnu, fbasic, s, apt_cap::CMIN, AP_P);
TEST_UN_OP_SUITE(mxs, fbasic, s, apt_cap::CMAX, AP_N);
TEST_UN_OP_SUITE(mds, fbasic, s, apt_cap::CMID, AP_N);
TEST_UN_OP_SUITE(mns, fbasic, s, apt_cap::CMIN, AP_N);
