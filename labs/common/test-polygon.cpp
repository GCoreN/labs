#include <stdexcept>
#include <cmath>
#include <boost/test/unit_test.hpp>

#include "polygon.hpp"
#include "base-types.hpp"

const double ACCURACY = 0.0000001;

BOOST_AUTO_TEST_SUITE(PolygonConstructor_ExpectedBehavior)

  BOOST_AUTO_TEST_CASE(Constructor_ValidValues_ReturnsEqualValues)
  {
    std::initializer_list<li::point_t> points = {{ 3.1,  5.1 },
                                                 { 8.1,  0.9 },
                                                 { -6.2, 1.5 }};
    li::Polygon polygon(points);

    BOOST_CHECK_CLOSE(polygon[0].x, 3.1, ACCURACY);
    BOOST_CHECK_CLOSE(polygon[0].y, 5.1, ACCURACY);
    BOOST_CHECK_CLOSE(polygon[2].x, -6.2, ACCURACY);
    BOOST_CHECK_CLOSE(polygon[2].y, 1.5, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Constructor_InvalidValues_ExceptionThrown)
  {
    std::initializer_list<li::point_t> points = {{ 3.1, 5.1 },
                                                 { 8.1, 0.9 }};

    BOOST_CHECK_THROW(li::Polygon polygon(points), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(PolygonSimpleFunctions_ExpectedBehavior)

  BOOST_AUTO_TEST_CASE(getArea_ValidValues_ReturnsCorrectCalculations)
  {
    std::initializer_list<li::point_t> points = {{ 1.0, 1.0 },
                                                       { 2.0, 0.0 },
                                                       { 0.0, 2.0 },
                                                       { 2.0, 2.0 }};
    li::Polygon polygon(points);

    BOOST_CHECK_CLOSE(polygon.getArea(), 1.0, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(getFrameRect_ValidValues_ReturnsEqualValues)
  {
    std::initializer_list<li::point_t> points = {{ 0.0, 0.0 },
                                                       { 1.0, 0.0 },
                                                       { 0.0, 1.0 },
                                                       { 1.0, 1.0 }};
    li::Polygon polygon(points);
    li::rectangle_t testrec{ 1.0, 1.0, { 0.5, 0.5 }};
    li::rectangle_t frame = polygon.getFrameRect();

    BOOST_CHECK_CLOSE(frame.width, testrec.width, ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, testrec.height, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.x, testrec.pos.x, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.y, testrec.pos.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(rotate_ValidValues_ReturnsEqualValues)
  {
    std::initializer_list<li::point_t> points = {{ 0.0, 0.0 },
                                                       { 1.0, 0.0 },
                                                       { 0.0, 1.0 },
                                                       { 1.0, 1.0 }};
    li::Polygon polygon(points);
    polygon.rotate(360);

    BOOST_CHECK_CLOSE(polygon[3].x, 1.0, ACCURACY);
    BOOST_CHECK_CLOSE(polygon[3].y, 1.0, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(PolygonScale_ExpectedBehavior)

  BOOST_AUTO_TEST_CASE(scale_InvalidValues_ExceptionThrown)
  {
    std::initializer_list<li::point_t> points = {{ 0.0, 0.0 },
                                                       { 1.0, 0.0 },
                                                       { 0.0, 1.0 },
                                                       { 1.0, 1.0 }};
    alferova::Polygon polygon(points);

    BOOST_CHECK_THROW(polygon.scale(0.0), std::invalid_argument);
    BOOST_CHECK_THROW(polygon.scale(-3.2), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(scale_ValidValues_ReturnsCorrectCalculations)
  {
    std::initializer_list<li::point_t> points = {{ 0.0, 0.0 },
                                                 { 1.0, 0.0 },
                                                 { 0.0, 1.0 },
                                                 { 1.0, 1.0 }};
    li::Polygon polygon(points);

    polygon.scale(1.0);

    BOOST_CHECK_CLOSE(polygon[0].x, 0.0, ACCURACY);
    BOOST_CHECK_CLOSE(polygon[0].y, 0.0, ACCURACY);

    polygon.scale(2.0);

    BOOST_CHECK_CLOSE(polygon[0].x, -0.5, ACCURACY);
    BOOST_CHECK_CLOSE(polygon[0].y, -0.5, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()
