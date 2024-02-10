// Assuming you have GoogleTest included in your project setup

#include <gtest/gtest.h>
#include "../includes/Vec3.h"
#include "../includes/ArrayT.h"

// Define the test suite name with TEST()
TEST(MyTestSuite, DotProduct) {
    Vec3 v1(1.0, 2.0, 0.0);
    Vec3 v2(-1.0, -3.0, 1.0);
    EXPECT_DOUBLE_EQ(v1.Dot(v2), -7.0); // Use EXPECT_DOUBLE_EQ for comparing floating-point numbers
}

TEST(MyTestSuite, AssignToScalar) {
    Vec3 v1(3, 5, 0);
    double val = 3;
    v1 = val;
    EXPECT_EQ(v1.x, 3);
    EXPECT_EQ(v1.y, 3);
}

TEST(MyTestSuite, MultiplyingByScalar) {
    Vec3 v1(5, 4, 0);
    double val = 3;
    v1 *= val;
    EXPECT_EQ(v1.x, 15);
    EXPECT_EQ(v1.y, 12);
}

TEST(MyTestSuite, MultiplyingByScalarOnTheLine) {
    Vec3 v1(2.0, 3.0, 0.0);
    double val = 2.0;
    Vec3 v2 = v1 * val;
    EXPECT_EQ(v2.x, 4.0);
    EXPECT_EQ(v2.y, 6.0);
}
