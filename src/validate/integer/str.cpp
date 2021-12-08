#include "../common.hpp"

template <index_t _Capacity, bool _Signed>
struct integer_str_impl
{
    std::string operator()(const std::string& istr) const
    {
        integer<_Capacity, _Signed> iov{istr};
        std::string result = iov.str(16);

        iov = istr;
        if (result != iov.str(16))
        {
            throw std::runtime_error("Assignment failed");
        }

        std::string strange = iov.str(6, "QWERTY");
        iov.set(strange, 6, "QWERTY");
        if (result != iov.str(16))
        {
            throw std::runtime_error("Custom conversion failed");
        }

        return result;
    }
};

static inline std::string boost_integer_str_u(const std::string& istr, index_t ic, index_t oc)
{
    boost_uint v{istr};
    return boost_uint_tou(v, oc);
}

static inline std::string boost_integer_str_s(const std::string& istr, index_t ic, index_t oc)
{
    boost_uint v{istr};
    return boost_uint_tos(v, oc);
}

static inline std::string ap_integer_str_u(const std::string& istr, index_t ic, index_t oc)
{
    return ap_tu(ap_dispatch_unary_op<false, integer_str_impl>(istr, ic), oc);
}

static inline std::string ap_integer_str_s(const std::string& istr, index_t ic, index_t oc)
{
    return ap_ts(ap_dispatch_unary_op<true, integer_str_impl>(istr, ic), oc);
}

TEST_SUITE_UOP(integer_str, s);
TEST_SUITE_UOP(integer_str, u);

TEST(integer_str, build)
{
    ap_uint_l a;
    a.set("1");
    a.set(std::string("1"));
    ap_uint_l b{"1"};
    ap_uint_l c{std::string("1")};
    b = "1";
    c = std::string("1");
    b.str();
    b = std::string(c);
}