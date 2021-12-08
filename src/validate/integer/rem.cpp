#include "../common.hpp"

template <index_t _CapacityL, index_t _CapacityR, bool _Signed, bool _Crossed>
struct integer_rem_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        if (_Crossed)
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, !_Signed> right{rstr};
            if (right == 0)
            {
                return "0x0";
            }
            return (left % right).str(16);
        }
        else
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, _Signed> right{rstr};
            if (right == 0)
            {
                return "0x0";
            }
            return (left % right).str(16);
        }
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_rem_impl_u : integer_rem_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_rem_impl_s : integer_rem_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_remx_impl_u : integer_rem_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_remx_impl_s : integer_rem_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

static inline std::string boost_integer_rem_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    if (right == 0)
    {
        return "0x0";
    }
    return boost_uint_tou(left % right, MAX(lc, rc));
}

static inline std::string boost_integer_rem_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_sint left{ap_ts(lstr, lc)};
    boost_sint right{ap_ts(rstr, rc)};
    if (right == 0)
    {
        return "0x0";
    }
    boost_uint out{left % right};
    return boost_uint_tos(out, MAX(lc, rc));
}

static inline std::string boost_integer_remx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    if (lc >= rc)
    {
        boost_uint left{ap_tu(lstr, lc)};
        boost_uint right{ap_tu(ap_ts(rstr, rc), lc)};
        if (right == 0)
        {
            return "0x0";
        }
        return boost_uint_tou(left % right, lc);
    }
    else
    {
        boost_sint left{ap_tu(lstr, lc)};
        boost_sint right{ap_ts(rstr, rc)};
        if (right == 0)
        {
            return "0x0";
        }
        boost_uint out{left % right};
        return boost_uint_tos(out, rc);
    }
}

static inline std::string boost_integer_remx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    if (lc > rc)
    {
        boost_sint left{ap_ts(lstr, lc)};
        boost_sint right{ap_tu(rstr, rc)};
        if (right == 0)
        {
            return "0x0";
        }
        boost_uint out{left % right};
        return boost_uint_tos(out, lc);
    }
    else
    {
        boost_uint left{ap_tu(ap_ts(lstr, lc), rc)};
        boost_uint right{ap_tu(rstr, rc)};
        if (right == 0)
        {
            return "0x0";
        }
        return boost_uint_tou(left % right, rc);
    }
}

static inline std::string ap_integer_rem_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_rem_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_rem_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_rem_impl_s>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_remx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_remx_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_remx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_remx_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_rem, s);
TEST_SUITE_BOPERATOR(integer_rem, u);
TEST_SUITE_BOPERATOR(integer_remx, s);
TEST_SUITE_BOPERATOR(integer_remx, u);

template <index_t _CapacityL, index_t _CapacityR, bool _Signed, bool _Crossed>
struct integer_srem_impl
{
    std::string operator()(const std::string& lstr, const std::string& rstr) const
    {
        if (_Crossed)
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, !_Signed> right{rstr};
            if (right == 0)
            {
                return "0x0";
            }
            return (left %= right).str(16);
        }
        else
        {
            integer<_CapacityL, _Signed> left{lstr};
            integer<_CapacityR, _Signed> right{rstr};
            if (right == 0)
            {
                return "0x0";
            }
            return (left %= right).str(16);
        }
    }
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_srem_impl_u : integer_srem_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_srem_impl_s : integer_srem_impl<_CapacityL, _CapacityR, _Signed, false>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_sremx_impl_u : integer_srem_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

template <index_t _CapacityL, index_t _CapacityR, bool _Signed>
struct integer_sremx_impl_s : integer_srem_impl<_CapacityL, _CapacityR, _Signed, true>
{
};

static inline std::string boost_integer_srem_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_uint left{ap_tu(lstr, lc)};
    boost_uint right{ap_tu(rstr, rc)};
    if (right == 0)
    {
        return "0x0";
    }
    return boost_uint_tou(left %= right, lc);
}

static inline std::string boost_integer_srem_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    boost_sint left{ap_ts(lstr, lc)};
    boost_sint right{ap_ts(rstr, rc)};
    if (right == 0)
    {
        return "0x0";
    }
    boost_uint out{left %= right};
    return boost_uint_tos(out, lc);
}

static inline std::string boost_integer_sremx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    if (lc >= rc)
    {
        boost_uint left{ap_tu(lstr, lc)};
        boost_uint right{ap_tu(ap_ts(rstr, rc), lc)};
        if (right == 0)
        {
            return "0x0";
        }
        return boost_uint_tou(left %= right, lc);
    }
    else
    {
        boost_sint left{ap_tu(lstr, lc)};
        boost_sint right{ap_ts(rstr, rc)};
        if (right == 0)
        {
            return "0x0";
        }
        boost_uint out{left %= right};
        return boost_uint_tou(out, lc);
    }
}

static inline std::string boost_integer_sremx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    if (lc > rc)
    {
        boost_sint left{ap_ts(lstr, lc)};
        boost_sint right{ap_tu(rstr, rc)};
        if (right == 0)
        {
            return "0x0";
        }
        boost_uint out{left %= right};
        return boost_uint_tos(out, lc);
    }
    else
    {
        boost_uint left{ap_tu(ap_ts(lstr, lc), rc)};
        boost_uint right{ap_tu(rstr, rc)};
        if (right == 0)
        {
            return "0x0";
        }
        return boost_uint_tos(left %= right, lc);
    }
}

static inline std::string ap_integer_srem_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_srem_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_srem_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_srem_impl_s>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_sremx_u(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<false, integer_sremx_impl_u>(lstr, rstr, lc, rc, oc);
}

static inline std::string ap_integer_sremx_s(const std::string& lstr, const std::string& rstr, index_t lc, index_t rc, index_t oc)
{
    return ap_dispatch_binary_op<true, integer_sremx_impl_s>(lstr, rstr, lc, rc, oc);
}

TEST_SUITE_BOPERATOR(integer_srem, s);
TEST_SUITE_BOPERATOR(integer_srem, u);
TEST_SUITE_BOPERATOR(integer_sremx, s);
TEST_SUITE_BOPERATOR(integer_sremx, u);