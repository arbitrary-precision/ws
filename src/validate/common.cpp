#include "common.hpp"

TEST(common, cap)
{
    ASSERT_EQ(ap_capb(1024), 1024 / 8);
    ASSERT_EQ(ap_capw(1024), 1024 / word_traits::bits);
}

TEST(common, sz)
{
    ASSERT_EQ(ap_sz(1024, AP_SZ_O), word_traits::bits);
    ASSERT_EQ(ap_sz(1024, AP_SZ_Q), 1024 / 4);
    ASSERT_EQ(ap_sz(1024, AP_SZ_H), 1024 / 2);
    ASSERT_EQ(ap_sz(1024, AP_SZ_M), 1024 / 4 * 3);
    ASSERT_EQ(ap_sz(1024, AP_SZ_F), 1024);

    ASSERT_EQ(ap_szb(1024, AP_SZ_O), word_traits::bytes);
    ASSERT_EQ(ap_szb(1024, AP_SZ_Q), 1024 / 4 / 8);
    ASSERT_EQ(ap_szb(1024, AP_SZ_H), 1024 / 2 / 8);
    ASSERT_EQ(ap_szb(1024, AP_SZ_M), 1024 / 4 * 3 / 8);
    ASSERT_EQ(ap_szb(1024, AP_SZ_F), 1024 / 8);

    ASSERT_EQ(ap_szw(1024, AP_SZ_O), 1);
    ASSERT_EQ(ap_szw(1024, AP_SZ_Q), 1024 / 4 / word_traits::bits);
    ASSERT_EQ(ap_szw(1024, AP_SZ_H), 1024 / 2 / word_traits::bits);
    ASSERT_EQ(ap_szw(1024, AP_SZ_M), 1024 / 4 * 3 / word_traits::bits);
    ASSERT_EQ(ap_szw(1024, AP_SZ_F), 1024 / word_traits::bits);
}

TEST(common, pb)
{
    ASSERT_EQ(ap_bp(AP_BP_ZD), "00");
    ASSERT_EQ(ap_bp(AP_BP_C0), "55");
    ASSERT_EQ(ap_bp(AP_BP_C1), "AA");
    ASSERT_EQ(ap_bp(AP_BP_FD), "FF");
}

TEST(common, ps)
{
    ASSERT_EQ(ap_sp(16, AP_SP_ZD), "0000");
    ASSERT_EQ(ap_sp(16, AP_SP_C0), "5555");
    ASSERT_EQ(ap_sp(16, AP_SP_C1), "AAAA");
    ASSERT_EQ(ap_sp(16, AP_SP_C2), "00FF");
    ASSERT_EQ(ap_sp(16, AP_SP_C3), "FF00");
    ASSERT_EQ(ap_sp(16, AP_SP_OL), "0001");
    ASSERT_EQ(ap_sp(16, AP_SP_OH), "8000");
    ASSERT_EQ(ap_sp(16, AP_SP_ML), "FFFE");
    ASSERT_EQ(ap_sp(16, AP_SP_MH), "7FFF");
    ASSERT_EQ(ap_sp(16, AP_SP_FD), "FFFF");
}

TEST(common, tu)
{
    ASSERT_EQ(ap_tu("0x" + ap_sp(32, AP_SP_ZD), 16), "0x0");
    ASSERT_EQ(ap_tu("0x" + ap_sp(32, AP_SP_C0), 16), "0x5555");
    ASSERT_EQ(ap_tu("0x" + ap_sp(32, AP_SP_C1), 16), "0xAAAA");
    ASSERT_EQ(ap_tu("0x" + ap_sp(32, AP_SP_C2), 16), "0xFF");
    ASSERT_EQ(ap_tu("0x" + ap_sp(32, AP_SP_C3), 16), "0xFF00");
    ASSERT_EQ(ap_tu("0x" + ap_sp(32, AP_SP_OL), 16), "0x1");
    ASSERT_EQ(ap_tu("0x" + ap_sp(32, AP_SP_OH), 16), "0x0");
    ASSERT_EQ(ap_tu("0x" + ap_sp(32, AP_SP_ML), 16), "0xFFFE");
    ASSERT_EQ(ap_tu("0x" + ap_sp(32, AP_SP_MH), 16), "0xFFFF");
    ASSERT_EQ(ap_tu("0x" + ap_sp(32, AP_SP_FD), 16), "0xFFFF");

    ASSERT_EQ(ap_tu("-0x1", 16), "0xFFFF");
}

TEST(common, ts)
{
    ASSERT_EQ(ap_ts("0x" + ap_sp(32, AP_SP_ZD), 16), "0x0");
    ASSERT_EQ(ap_ts("0x" + ap_sp(32, AP_SP_C0), 16), "0x5555");
    ASSERT_EQ(ap_ts("0x" + ap_sp(32, AP_SP_C1), 16), "-0x5556");
    ASSERT_EQ(ap_ts("0x" + ap_sp(32, AP_SP_C2), 16), "0xFF");
    ASSERT_EQ(ap_ts("0x" + ap_sp(32, AP_SP_C3), 16), "-0x100");
    ASSERT_EQ(ap_ts("0x" + ap_sp(32, AP_SP_OL), 16), "0x1");
    ASSERT_EQ(ap_ts("0x" + ap_sp(32, AP_SP_OH), 16), "0x0");
    ASSERT_EQ(ap_ts("0x" + ap_sp(32, AP_SP_ML), 16), "-0x2");
    ASSERT_EQ(ap_ts("0x" + ap_sp(32, AP_SP_MH), 16), "-0x1");
    ASSERT_EQ(ap_ts("0x" + ap_sp(32, AP_SP_FD), 16), "-0x1");

    ASSERT_EQ(ap_ts("0x" + ap_sp(16, AP_SP_ZD), 16), "0x0");
    ASSERT_EQ(ap_ts("0x" + ap_sp(16, AP_SP_C0), 16), "0x5555");
    ASSERT_EQ(ap_ts("0x" + ap_sp(16, AP_SP_C1), 16), "-0x5556");
    ASSERT_EQ(ap_ts("0x" + ap_sp(16, AP_SP_C2), 16), "0xFF");
    ASSERT_EQ(ap_ts("0x" + ap_sp(16, AP_SP_C3), 16), "-0x100");
    ASSERT_EQ(ap_ts("0x" + ap_sp(16, AP_SP_OL), 16), "0x1");
    ASSERT_EQ(ap_ts("0x" + ap_sp(16, AP_SP_OH), 16), "-0x8000");
    ASSERT_EQ(ap_ts("0x" + ap_sp(16, AP_SP_ML), 16), "-0x2");
    ASSERT_EQ(ap_ts("0x" + ap_sp(16, AP_SP_MH), 16), "0x7FFF");
    ASSERT_EQ(ap_ts("0x" + ap_sp(16, AP_SP_FD), 16), "-0x1");

    ASSERT_EQ(ap_ts("-0x1", 16), "-0x1");
}

TEST(common, gu)
{
    ASSERT_EQ(ap_gu(32, AP_SP_ZD), "0x0");
    ASSERT_EQ(ap_gu(32, AP_SP_C0), "0x55555555");
    ASSERT_EQ(ap_gu(32, AP_SP_C1), "0xAAAAAAAA");
    ASSERT_EQ(ap_gu(32, AP_SP_C2), "0xFF00FF");
    ASSERT_EQ(ap_gu(32, AP_SP_C3), "0xFF00FF00");
    ASSERT_EQ(ap_gu(32, AP_SP_OL), "0x1");
    ASSERT_EQ(ap_gu(32, AP_SP_OH), "0x80000000");
    ASSERT_EQ(ap_gu(32, AP_SP_ML), "0xFFFFFFFE");
    ASSERT_EQ(ap_gu(32, AP_SP_MH), "0x7FFFFFFF");
    ASSERT_EQ(ap_gu(32, AP_SP_FD), "0xFFFFFFFF");
}

TEST(common, gs)
{
    ASSERT_EQ(ap_gs(32, AP_SP_ZD), "0x0");
    ASSERT_EQ(ap_gs(32, AP_SP_C0), "0x55555555");
    ASSERT_EQ(ap_gs(32, AP_SP_C1), "-0x55555556");
    ASSERT_EQ(ap_gs(32, AP_SP_C2), "0xFF00FF");
    ASSERT_EQ(ap_gs(32, AP_SP_C3), "-0xFF0100");
    ASSERT_EQ(ap_gs(32, AP_SP_OL), "0x1");
    ASSERT_EQ(ap_gs(32, AP_SP_OH), "-0x80000000");
    ASSERT_EQ(ap_gs(32, AP_SP_ML), "-0x2");
    ASSERT_EQ(ap_gs(32, AP_SP_MH), "0x7FFFFFFF");
    ASSERT_EQ(ap_gs(32, AP_SP_FD), "-0x1");
}
