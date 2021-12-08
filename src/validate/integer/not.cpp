#include "../common.hpp"

template <index_t _Capacity, bool _Signed>
struct integer_not_impl
{
    std::string operator()(const std::string& istr) const
    {
        integer<_Capacity, _Signed> iov{istr};
        iov = ~iov;
        return iov.str(16);
    }
};

static inline std::string boost_integer_not_u(const std::string& istr, index_t ic, index_t oc)
{
    boost_uint v{istr};
    v = ~v;
    return boost_uint_tou(v, ic);
}

static inline std::string boost_integer_not_s(const std::string& istr, index_t ic, index_t oc)
{
    boost_uint v{istr};
    v = ~v;
    return boost_uint_tos(v, ic);
}

static inline std::string ap_integer_not_u(const std::string& istr, index_t ic, index_t oc)
{
    return ap_dispatch_unary_op<false, integer_not_impl>(istr, ic);
}

static inline std::string ap_integer_not_s(const std::string& istr, index_t ic, index_t oc)
{
    return ap_dispatch_unary_op<true, integer_not_impl>(istr, ic);
}

TEST_SUITE_UOP(integer_not, s);
TEST_SUITE_UOP(integer_not, u);
