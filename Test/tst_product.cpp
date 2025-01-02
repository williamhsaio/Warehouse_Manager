#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "../product.h"

using namespace testing;

TEST(Product, getName)
{
    Product p("T_Product", "A1", 200, 0);
    EXPECT_EQ(p.getName(), "T_Product") << "You fucked up.";
}
TEST(Product, product_SetName)
{
    Product p("T_Product", "A1", 200, 0);
    p.setName("Frog");
    EXPECT_EQ(p.getName(), "Frog") << "You fucked up.";
}
