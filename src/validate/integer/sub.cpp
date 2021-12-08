#include "../common.hpp"

template <index_t _CapacityL, index_t _CapacityR, bool _Signed, bool _Crossed>
struct integer_sub_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        if (_Crossed)
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, !_Signed> right{rstr};
            return (left - right).str(16);
        }
        else
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, _Signed> right{rstr};
            return (left - right).str(16);
        }
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_sub_impl_u : integer_sub_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_sub_impl_s : integer_sub_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_subx_impl_u : integer_sub_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_subx_impl_s : integer_sub_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

static inline std::string boost_integer_sub_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    return boost_uint_tou(left - right, MAX(lc, rc));
}

static inline std::string boost_integer_sub_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    return boost_uint_tos(left - right, MAX(lc, rc));
}

static inline std::string boost_integer_subx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    if (lc >= rc)
    {
        return boost_uint_tou(left - right, lc);
    }
    else
    {
        return boost_uint_tos(left - right, rc);
    }
}

static inline std::string boost_integer_subx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    if (lc > rc)
    {
        return boost_uint_tos(left - right, lc);
    }
    else
    {
        return boost_uint_tou(left - right, rc);
    }
}

static inline std::string ap_integer_sub_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_sub_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_sub_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_sub_impl_s>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_subx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_subx_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_subx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_subx_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_sub, s);
TEST_SUITE_BOPERATOR(integer_sub, u);
TEST_SUITE_BOPERATOR(integer_subx, s);
TEST_SUITE_BOPERATOR(integer_subx, u);

template <index_t _CapacityL, index_t _CapacityR, bool _Signed, bool _Crossed>
struct integer_ssub_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        if (_Crossed)
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, !_Signed> right{rstr};
            return (left -= right).str(16);
        }
        else
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, _Signed> right{rstr};
            return (left -= right).str(16);
        }
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_ssub_impl_u : integer_ssub_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_ssub_impl_s : integer_ssub_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_ssubx_impl_u : integer_ssub_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_ssubx_impl_s : integer_ssub_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

static inline std::string boost_integer_ssub_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    return boost_uint_tou(left -= right, lc);
}

static inline std::string boost_integer_ssub_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    return boost_uint_tos(left -= right, lc);
}

static inline std::string boost_integer_ssubx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_ts(rstr, rc)};
    return boost_uint_tou(left -= right, lc);
}

static inline std::string boost_integer_ssubx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_ts(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    return boost_uint_tos(left -= right, lc);
}

static inline std::string ap_integer_ssub_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_ssub_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_ssub_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_ssub_impl_s>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_ssubx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_ssubx_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_ssubx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_ssubx_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_ssub, s);
TEST_SUITE_BOPERATOR(integer_ssub, u);
TEST_SUITE_BOPERATOR(integer_ssubx, s);
TEST_SUITE_BOPERATOR(integer_ssubx, u);
