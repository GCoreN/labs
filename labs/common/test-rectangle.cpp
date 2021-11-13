#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include <cmath>

#include "rectangle.hpp"
#include "base-types.hpp"

const double ACCURACY = 0.0000001;

BOOST_AUTO_TEST_SUITE(RectangleConstructor_ExcpectedBehaviorWithDifferentValues)

  BOOST_AUTO_TEST_CASE(rectangleConstructor_ValidValues_ReturnsEqualValue)
  {
    double width = 2.0;
    double height = 4.0;
    li::point_t pos = { 0.0, 0.0 };
    li::Rectangle rec = { width, height, pos };

    BOOST_CHECK_CLOSE(rec.getWidth(), width, ACCURACY);
    BOOST_CHECK_CLOSE(rec.getHeight(), height, ACCURACY);
    BOOST_CHECK_EQUAL(rec.getPos().x, pos.x);
    BOOST_CHECK_EQUAL(rec.getPos().y, pos.y);
  }

  BOOST_AUTO_TEST_CASE(rectangleConstructor_InvalidWidth_ExceptionThrown)
  {
    BOOST_CHECK_THROW(li::Rectangle rec(0.0, 1.2, { 0.0, 0.0 }), std::invalid_argument);
    BOOST_CHECK_THROW(li::Rectangle rec(-2.1, 1.2, { 0.0, 0.0 }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rectangleConstructor_InvalidHeight_ExceptionThrown)
  {
    BOOST_CHECK_THROW(li::Rectangle rec(1.2, 0.0, { 0.0, 0.0 }), std::invalid_argument);
    BOOST_CHECK_THROW(li::Rectangle rec(1.2, -2.1, { 0.0, 0.0 }), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleGetArea_ExcpectedBehaviorInWork)

  BOOST_AUTO_TEST_CASE(getArea_ValidValues_Calculated)
  {
    double width = 2.1;
    double height = 3.4;
    li::Rectangle rec(width, height, { 1.1, 1.1 });

    BOOST_CHECK_CLOSE(rec.getArea(), width * height, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleMove_ExcpectedBehaviorInWork)

  BOOST_AUTO_TEST_CASE(move_ValidPoint_ReturnsEqualValue)
  {
    double x = 3.2;
    double y = -1.2;
    li::Rectangle rec(3.2, 1.2, { 0.0, -2 });

    rec.move({ x, y });

    BOOST_CHECK_CLOSE(rec.getPos().x, x, ACCURACY);
    BOOST_CHECK_CLOSE(rec.getPos().y, y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(getAreaAfterMove_ValidPoint_ReturnsEqualValue)
  {
    double width = 2.1;
    double height = 3.4;
    li::Rectangle rec(width, height, { 1.1, 1.1 });

    rec.move({ 3.1, 4.1 });

    BOOST_CHECK_CLOSE(rec.getArea(), width * height, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(move_ValidValues_Calculated)
  {
    double dx = 1.9;
    double dy = -4.1;
    double x = 3.2;
    double y = -1.2;
    li::Rectangle rec(3.2, 1.2, { x, y });

    rec.move(dx, dy);

    BOOST_CHECK_CLOSE(rec.getPos().x, x + dx, ACCURACY);
    BOOST_CHECK_CLOSE(rec.getPos().y, y + dy, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(getAreaAfterMove_ValidValues_ReturnsEqualValue)
  {
    double width = 2.1;
    double height = 3.4;
    li::Rectangle rec(width, height, { 1.1, 1.1 });

    rec.move(3.1, 4.1);

    BOOST_CHECK_CLOSE(rec.getArea(), width * height, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleScale_ExcpectedBehaviorInWork)

  BOOST_AUTO_TEST_CASE(getAreaAfterScale_ValidValue_Calculated)
  {
    double width = 2.1;
    double height = 3.4;
    li::Rectangle rec(width, height, { 1.1, 1.1 });

    double coefficient = 3.0;
    rec.scale(coefficient);

    BOOST_CHECK_CLOSE(rec.getArea(), width * height * coefficient * coefficient, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(getPositionAfterScale_ValidValue_ReturnsEqualValue)
  {
    double x = 3.2;
    double y = -1.2;
    li::Rectangle rec(3.2, 1.2, { x, y });

    rec.scale(3.0);

    BOOST_CHECK_CLOSE(rec.getPos().x, x, ACCURACY);
    BOOST_CHECK_CLOSE(rec.getPos().y, y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(scale_InvalidValue_ExceptionThrown)
  {
    li::Rectangle rec(3.2, 1.2, { 2.2, 3.3 });

    BOOST_CHECK_THROW(rec.scale(-1.0), std::invalid_argument);
    BOOST_CHECK_THROW(rec.scale(0.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleGetFrameRect_ExcpectedBehaviorInWork)

  BOOST_AUTO_TEST_CASE(getFrameRect_ValidValues_ReturnsEqualValues)
  {
    double x = 3.2;
    double y = 2.3;
    double width = 2.1;
    double height = 2.2;

    li::Rectangle rec(width, height, { x, y });
    li::rectangle_t frame = rec.getFrameRect();

    BOOST_CHECK_CLOSE(frame.width, width, ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, height, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.x, x, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.y, y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(getFrameRectAfterMove_ValidPoint_ReturnsEqualValues)
  {
    double x = 3.2;
    double y = 2.3;
    double width = 2.1;
    double height = 2.2;
    li::Rectangle rec(width, height, { x, y });
    double x1 = 2.0;
    double y1 = 3.1;

    rec.move({ x1, y1 });

    li::rectangle_t frame = rec.getFrameRect();

    BOOST_CHECK_CLOSE(frame.width, width, ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, height, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.x, x1, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.y, y1, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(getFrameRectAfterMove_ValidValues_ReturnsEqualValues)
  {
    double x = 3.2;
    double y = 2.3;
    double width = 2.1;
    double height = 2.2;
    li::Rectangle rec(width, height, { x, y });
    double dx = 2.0;
    double dy = 3.1;

    rec.move(dx, dy);

    li::rectangle_t frame = rec.getFrameRect();

    BOOST_CHECK_CLOSE(frame.width, width, ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, height, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.x, x + dx, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.y, y + dy, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(getFrameRectAfterScale_ValidValue_ReturnsCorrectCalculations)
  {
    double x = 3.2;
    double y = 2.3;
    double width = 2.1;
    double height = 2.2;
    li::Rectangle rec(width, height, { x, y });
    double coefficient = 3.0;

    rec.scale(coefficient);

    li::rectangle_t frame = rec.getFrameRect();

    BOOST_CHECK_CLOSE(frame.width, width * coefficient, ACCURACY);
    BOOST_CHECK_CLOSE(frame.height, height * coefficient, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.x, x, ACCURACY);
    BOOST_CHECK_CLOSE(frame.pos.y, y, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(rectangleRotate_ExpectedBehavior)

  BOOST_AUTO_TEST_CASE(getPosAfterRotate_ValidValues_ReturnsEqualValues)
  {
    li::Rectangle rec(2.0, 2.0, { 0.0, 0.0 });
    li::point_t center = rec.getPos();

    rec.rotate(45);

    BOOST_CHECK_CLOSE(rec.getPos().x, center.x, ACCURACY);
    BOOST_CHECK_CLOSE(rec.getPos().y, center.y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(getFrameRectAfterRotate_ValidValues_ReturnsAnotherFrame)
  {
    li::Rectangle rec(2.0, 2.0, { 0.0, 0.0 });

    rec.rotate(45);

    BOOST_CHECK_CLOSE(rec.getFrameRect().width, 2.0 * sqrt(2.0), ACCURACY);
    BOOST_CHECK_CLOSE(rec.getFrameRect().height, 2.0 * sqrt(2.0), ACCURACY);
    BOOST_CHECK_CLOSE(rec.getFrameRect().pos.x, 0.0, ACCURACY);
    BOOST_CHECK_CLOSE(rec.getFrameRect().pos.y, 0.0, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()
