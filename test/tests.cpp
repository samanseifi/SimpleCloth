//
// Created by saman on 10/29/20.
//

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE my_unit_tests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include "../includes/Vec3.h"
#include "../includes/ArrayT.h"


BOOST_AUTO_TEST_SUITE(my_testsuite)

    BOOST_AUTO_TEST_CASE(dot_product)
    {
        Vec3 v1(1.0, 2.0, 0.0);
        Vec3 v2(-1.0, -3.0, 1.0);
        BOOST_TEST ( v1.Dot(v2) == -7.0);
    }

    BOOST_AUTO_TEST_CASE(assign_to_scalar)
    {
        Vec3 v1(3, 5, 0);
        double val = 3;
        v1 = val;
        BOOST_TEST (v1.x == 3);
        BOOST_TEST (v1.y == 3);
    }
    BOOST_AUTO_TEST_CASE(multiplying_by_scalar)
    {
        Vec3 v1(5, 4, 0);
        double val = 3;
        v1 *= val;
        BOOST_TEST (v1.x == 15);
        BOOST_TEST (v1.y == 12);
    }
    BOOST_AUTO_TEST_CASE(multiplying_by_scalar_on_the_line)
    {
        Vec3 v1(2.0, 3.0, 0.0);
        double val = 2.0;
        Vec3 v2 = v1 * val;
        BOOST_TEST (v2.x == 4.0);
        BOOST_TEST (v2.y == 6.0);
    }
    
BOOST_AUTO_TEST_SUITE_END()
