#include <stdexcept>
#include <cmath>
#include <boost/test/unit_test.hpp>

#include "circle.hpp"
#include "base-types.hpp"

const double ACCURACY = 0.0000001;

BOOST_AUTO_TEST_SUITE(CircleConstructor_ExcpectedBehaviorWithDifferentValues)

  BOOST_AUTO_TEST_CASE(circleConstructor_ValidValues_ReturnsEqualValue)
  {
    double radius = 5.2;
    li::point_t pos = { 3.9, -1.0 };
    li::Circle cir = { radius, pos };

    BOOST_CHECK_CLOSE(cir.getRadius(), radius, ACCURACY);
    BOOST_CHECK_EQUAL(cir.getPos().x, pos.x);
    BOOST_CHECK_EQUAL(cir.getPos().y, pos.y);
  }

  BOOST_AUTO_TEST_CASE(circleConstructor_InvalidRadius_ExceptionThrown)
  {
    BOOST_CHECK_THROW(li::Circle cir(0.0, { 0.0, 0.0 }), std::invalid_argument);
    BOOST_CHECK_THROW(li::Circle cir(-2.1, { 0.0, 0.0 }), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleGetArea_ExcpectedBehaviorInWork)

  BOOST_AUTO_TEST_CASE(getArea_ValidValues_Calculated)
  {
    double radius = 2.1;
    li::Circle cir(radius, { 1.1, 1.1 });

    BOOST_CHECK_CLOSE(cir.getArea(), M_PI * radius * radius, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleMove_ExcpectedBehaviorInWork)

  BOOST_AUTO_TEST_CASE(move_ValidPoint_ReturnsEqualValue)
  {
    double x = 3.2;
    double y = -1.2;
    alferova::Circle cir(5.3, { 0.0, -2 });
    cir.move({ x, y });

    BOOST_CHECK_CLOSE(cir.getPos().x, x, ACCURACY);
    BOOST_CHECK_CLOSE(cir.getPos().y, y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(getAreaAfterMove_ValidPoint_ReturnsEqualValue)
  {
    double radius = 2.1;
    li::Circle cir(radius, { 1.1, 1.1 });

    cir.move({ 3.1, 4.1 });

    BOOST_CHECK_CLOSE(cir.getArea(), M_PI * radius * radius, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(move_ValidValues_Calculated)
  {
    double dx = 1.9;
    double dy = -4.1;
    double x = 3.2;
    double y = -1.2;
    li::Circle cir(1.2, { x, y });

    cir.move(dx, dy);

    BOOST_CHECK_CLOSE(cir.getPos().x, x + dx, ACCURACY);
    BOOST_CHECK_CLOSE(cir.getPos().y, y + dy, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(getAreaAfterMove_ValidValues_ReturnsEqualValue)
  {
    double radius = 2.1;
    li::Circle cir(radius, { 1.1, 1.1 });

    cir.move(3.1, 4.1);

    BOOST_CHECK_CLOSE(cir.getArea(), M_PI * radius * radius, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleScale_ExcpectedBehaviorInWork)

  BOOST_AUTO_TEST_CASE(getAreaAfterScale_ValidValue_Calculated)
  {
    double radius = 2.1;
    li::Circle cir(radius, { 1.1, 1.1 });
    double coefficient = 3.0;

    cir.scale(coefficient);

    BOOST_CHECK_CLOSE(cir.getArea(), M_PI * radius * radius * coefficient * coefficient, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(getPositionAfterScale_ValidValue_ReturnsEqualValue)
  {
    double x = 3.2;
    double y = -1.2;
    li::Circle cir(4.8, { x, y });

    cir.scale(3.0);

    BOOST_CHECK_CLOSE(cir.getPos().x, x, ACCURACY);
    BOOST_CHECK_CLOSE(cir.getPos().y, y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(scale_InvalidValue_ExceptionThrown)
  {
    li::Circle cir(1.2, { 2.2, 3.3 });

    BOOST_CHECK_THROW(cir.scale(-1.0), std::invalid_argument);
    BOOST_CHECK_THROW(cir.scale(0.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleGetFrameRect_ExcpectedBehaviorInWork)

  BOOST_AUTO_TEST_CASE(getFrameRect_ValidValues_ReturnsCorrectCalculations)
  {
    double x = 3.2;
    double y = 2.3;
    double radius = 2.1;
    li::Circle cir(radius, { x, y });
    li::rectangle_t frame = cir.getFrameRect();

    BOOST_CHECK_CLOSE(frame.width, radius * 2, ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, radius * 2, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.x, x, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.y, y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(getFrameRectAfterMove_ValidPoint_ReturnsCorrectCalculations)
  {
    double x = 3.2;
    double y = 2.3;
    double radius = 2.1;
    li::Circle cir(radius, { x, y });
    double x1 = 2.0;
    double y1 = 3.1;

    cir.move({ 2.0, 3.1 });

    li::rectangle_t frame = cir.getFrameRect();

    BOOST_CHECK_CLOSE(frame.width, radius * 2, ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, radius * 2, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.x, x1, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.y, y1, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(getFrameRectAfterMove_ValidValues_ReturnsCorrectCalculations)
  {
    double x = 3.2;
    double y = 2.3;
    double radius = 2.1;
    li::Circle cir(radius, { x, y });
    double dx = 2.0;
    double dy = 3.1;

    cir.move(dx, dy);

    li::rectangle_t frame = cir.getFrameRect();

    BOOST_CHECK_CLOSE(frame.width, radius * 2, ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, radius * 2, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.x, x + dx, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.y, y + dy, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(getFrameRectAfterScale_ValidValue_ReturnsCorrectCalculations)
  {
    double x = 3.2;
    double y = 2.3;
    double radius = 2.1;
    li::Circle cir(radius, { x, y });
    double coefficient = 3.0;

    cir.scale(coefficient);

    li::rectangle_t frame = cir.getFrameRect();

    BOOST_CHECK_CLOSE(frame.width, radius * 2 * coefficient, ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, radius * 2 * coefficient, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.x, x, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.y, y, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()
