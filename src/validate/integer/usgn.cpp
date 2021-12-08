#include "../common.hpp"

template <index_t _Capacity, bool _Signed>
struct integer_uplus_impl
{
    std::string operator()(const std::string& istr) const
    {
        integer<_Capacity, _Signed> iov{istr};
        integer<_Capacity, _Signed> val = +iov;
        return val.str(16);
    }
};

static inline std::string boost_integer_uplus_u(const std::string& istr, index_t ic, index_t oc)
{
    boost_uint v{istr};
    return boost_uint_tou(v, ic);
}

static inline std::string boost_integer_uplus_s(const std::string& istr, index_t ic, index_t oc)
{
    boost_uint v{istr};
    return boost_uint_tos(v, ic);
}

static inline std::string ap_integer_uplus_u(const std::string& istr, index_t ic, index_t oc)
{
    return ap_dispatch_unary_op<false, integer_uplus_impl>(istr, ic);
}

static inline std::string ap_integer_uplus_s(const std::string& istr, index_t ic, index_t oc)
{
    return ap_dispatch_unary_op<true, integer_uplus_impl>(istr, ic);
}

TEST_SUITE_UOP(integer_uplus, s);
TEST_SUITE_UOP(integer_uplus, u);

template <index_t _Capacity, bool _Signed>
struct integer_uminus_impl
{
    std::string operator()(const std::string& istr) const
    {
        integer<_Capacity, _Signed> iov{istr};
        integer<_Capacity, _Signed> val = -iov;
        return val.str(16);
    }
};

static inline std::string boost_integer_uminus_u(const std::string& istr, index_t ic, index_t oc)
{
    boost_sint v{istr};
    v = -v;
    boost_uint vv{v};
    return boost_uint_tou(vv, ic);
}

static inline std::string boost_integer_uminus_s(const std::string& istr, index_t ic, index_t oc)
{
    boost_sint v{istr};
    v = -v;
    boost_uint vv{v};
    return boost_uint_tos(vv, ic);
}

static inline std::string ap_integer_uminus_u(const std::string& istr, index_t ic, index_t oc)
{
    return ap_dispatch_unary_op<false, integer_uminus_impl>(istr, ic);
}

static inline std::string ap_integer_uminus_s(const std::string& istr, index_t ic, index_t oc)
{
    return ap_dispatch_unary_op<true, integer_uminus_impl>(istr, ic);
}

TEST_SUITE_UOP(integer_uminus, s);
TEST_SUITE_UOP(integer_uminus, u);
