#include <gtest/gtest.h>
#include "../src/expresso.h"

TEST(EXPRESSIONS, Trig)
{
    Expresso expresso{"2 + 55 - 6 / sin ( 90 ) * 76 * cos0"};

    ASSERT_EQ(-399, static_cast<int>(expresso.evaluate()));
}

TEST(EXPRESSIONS, PowerPrecedence)
{
    Expresso expresso{"3^2^3"};

    // assert 3^2^3 = 3^(2^3)
    ASSERT_EQ(6561, static_cast<int>(expresso.evaluate()));
}

TEST(EXPRESSIONS, SuperfluousBrackets)
{
    Expresso expresso{"(5)+((1+2)*4)"};

    ASSERT_EQ(17, static_cast<int>(expresso.evaluate()));
}

TEST(EXPRESSIONS, Unary)
{
    Expresso expresso{"-1 + sin90"};

    ASSERT_EQ(0, static_cast<int>(expresso.evaluate()));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
