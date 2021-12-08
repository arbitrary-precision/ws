#include "../common.hpp"

template <index_t _Capacity, bool _Signed>
struct integer_preinc_impl
{
    std::string operator()(const std::string& istr) const
    {
        integer<_Capacity, _Signed> iov{istr};
        integer<_Capacity, _Signed> val = ++iov;
        if (val.str(16) != iov.str(16))
        {
            throw std::runtime_error("preincrement: supposed new value and actual value does not match.");
        }
        return iov.str(16);
    }
};

static inline std::string boost_integer_preinc_u(const std::string& istr, index_t ic, index_t oc)
{
    boost_uint v{istr};
    ++v;
    return boost_uint_tou(v, ic);
}

static inline std::string boost_integer_preinc_s(const std::string& istr, index_t ic, index_t oc)
{
    boost_uint v{istr};
    ++v;
    return boost_uint_tos(v, ic);
}

static inline std::string ap_integer_preinc_u(const std::string& istr, index_t ic, index_t oc)
{
    return ap_dispatch_unary_op<false, integer_preinc_impl>(istr, ic);
}

static inline std::string ap_integer_preinc_s(const std::string& istr, index_t ic, index_t oc)
{
    return ap_dispatch_unary_op<true, integer_preinc_impl>(istr, ic);
}

TEST_SUITE_UOP(integer_preinc, s);
TEST_SUITE_UOP(integer_preinc, u);

template <index_t _Capacity, bool _Signed>
struct integer_postinc_impl
{
    std::string operator()(const std::string& istr) const
    {
        integer<_Capacity, _Signed> iov{istr};
        integer<_Capacity, _Signed> val = iov++;
        if (val.str(16) != integer<_Capacity, _Signed>(istr).str(16))
        {
            throw std::runtime_error("postincrement: supposed old value and actual old value does not match.");
        }
        return iov.str(16);
    }
};

static inline std::string boost_integer_postinc_u(const std::string& istr, index_t ic, index_t oc)
{
    boost_uint v{istr};
    ++v;
    return boost_uint_tou(v, ic);
}

static inline std::string boost_integer_postinc_s(const std::string& istr, index_t ic, index_t oc)
{
    boost_uint v{istr};
    ++v;
    return boost_uint_tos(v, ic);
}

static inline std::string ap_integer_postinc_u(const std::string& istr, index_t ic, index_t oc)
{
    return ap_dispatch_unary_op<false, integer_postinc_impl>(istr, ic);
}

static inline std::string ap_integer_postinc_s(const std::string& istr, index_t ic, index_t oc)
{
    return ap_dispatch_unary_op<true, integer_postinc_impl>(istr, ic);
}

TEST_SUITE_UOP(integer_postinc, s);
TEST_SUITE_UOP(integer_postinc, u);
