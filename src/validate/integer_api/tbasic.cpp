#include "../common.hpp"

static inline std::string tohex(unsigned long long a)
{
    char buff[50];
    sprintf(buff, "0x%llX", a);
    return std::string(buff);
}

static inline std::string boost_xinteger_tbasic_u(const std::string& istr, index_t ic, index_t oc)
{
    boost_uint v{istr};
    return ap_tu(tohex(static_cast<unsigned long long>(v)), oc);
}

static inline std::string boost_xinteger_tbasic_s(const std::string& istr, index_t ic, index_t oc)
{
    return ap_ts(boost_xinteger_tbasic_u(istr, ic, oc), oc);
}

static inline std::string ap_xinteger_tbasic_u(const std::string& istr, index_t ic, index_t oc)
{
    AP_REGISTER_D(i, ap_capw(ic));
    uinteger_fstr(i, istr.c_str(), istr.size(), 16, "0123456789ABCDEF");
    return tohex(uinteger_tbasic(rregister(i)));
}

static inline std::string ap_xinteger_tbasic_s(const std::string& istr, index_t ic, index_t oc)
{
    AP_REGISTER_D(i, ap_capw(ic));
    sinteger_fstr(i, istr.c_str(), istr.size(), 16, "0123456789ABCDEF");
    return tohex(sinteger_tbasic(rregister(i)));
}

TEST_SUITE_UOP(xinteger_tbasic, s);
TEST_SUITE_UOP(xinteger_tbasic, u);
