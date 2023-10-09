#include <stdio.h>
#include <iostream>
#include <glib-2.0/glib.h>
#include <glib-2.0/glib/gvariant.h>
#include <gtest/gtest.h>

#define TEST_EQUAL "equal"
#define TEST_GREATER "greater than"
#define TEST_LESSER "less than"

struct gvariant_t {
    GVariant* lhd = nullptr;
    GVariant* rhd = nullptr;
    gvariant_t(const gchar* l_t, int val, const gchar* r_t, int val2)
    {
        lhd = g_variant_new(l_t, val);
        rhd = g_variant_new(r_t, val2);
    }
};

std::string function_test(gvariant_t* gvariant) {
    int ret = g_variant_compare(gvariant->lhd, gvariant->rhd);
    if (ret == 0) {
        return std::string("equal");
    }
    else if (ret < 0) {
        return std::string("less than");
    }
    else {
        return std::string("greater than");
    }
}

TEST(GLIB_TEST, COMPERATION_LESSER) {
    EXPECT_EQ(
        function_test(new gvariant_t("u", 40, "u", 60)),
        TEST_LESSER
    );
}


TEST(GLIB_TEST, COMPERATION_EQUAL) {
    EXPECT_EQ(
        function_test(new gvariant_t("u", 60, "u", 60)),
        TEST_EQUAL
    );
}

TEST(GLIB_TEST, COMPERATION_GREATER) {
    EXPECT_EQ(
        function_test(new gvariant_t("u", 60, "u", 30)), 
        TEST_GREATER
    );
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}