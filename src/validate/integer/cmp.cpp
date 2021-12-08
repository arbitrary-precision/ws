#include "../common.hpp"

template <index_t _CapacityL, index_t _CapacityR, bool _Signed, bool _Crossed>
struct integer_cmp_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        std::string result;

        if (_Crossed)
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, !_Signed> right{rstr};
            result = std::to_string(left.cmp(right));
        }
        else
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, _Signed> right{rstr};
            result = std::to_string(left.cmp(right));
        }

        return result;
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_cmp_impl_u : integer_cmp_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_cmp_impl_s : integer_cmp_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_cmpx_impl_u : integer_cmp_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_cmpx_impl_s : integer_cmp_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

static inline std::string boost_integer_cmp_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    return std::to_string(left.compare(right));
}

static inline std::string boost_integer_cmp_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_sint left{ap_ts(lstr, lc)};
    boost_sint right{ap_ts(rstr, rc)};
    return std::to_string(left.compare(right));
}

static inline std::string boost_integer_cmpx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    if (rc > lc)
    {
        boost_sint left{ap_ts(ap_tu(lstr, lc), rc)};
        boost_sint right{ap_ts(rstr, rc)};
        return std::to_string(left.compare(right));
    }
    else
    {
        boost_uint left{ap_tu(lstr, lc)};
        boost_uint right{ap_tu(ap_ts(rstr, rc), lc)};
        return std::to_string(left.compare(right));
    }
}

static inline std::string boost_integer_cmpx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    if (lc > rc)
    {
        boost_sint left{ap_ts(lstr, lc)};
        boost_sint right{ap_ts(ap_tu(rstr, rc), lc)};
        return std::to_string(left.compare(right));
    }
    else
    {
        boost_uint left{ap_tu(ap_ts(lstr, lc), rc)};
        boost_uint right{ap_tu(rstr, rc)};
        return std::to_string(left.compare(right));
    }
}

static inline std::string ap_integer_cmp_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_cmp_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_cmp_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_cmp_impl_s>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_cmpx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_cmpx_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_cmpx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_cmpx_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_cmp, s);
TEST_SUITE_BOPERATOR(integer_cmp, u);
TEST_SUITE_BOPERATOR(integer_cmpx, s);
TEST_SUITE_BOPERATOR(integer_cmpx, u);
