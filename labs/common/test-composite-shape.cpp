#include <stdexcept>
#include <cmath>
#include <boost/test/unit_test.hpp>

#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "base-types.hpp"

const double ACCURACY = 0.0000001;

BOOST_AUTO_TEST_SUITE(CompositeShape_SimpleFunctions_ExpectedBehavior)

  BOOST_AUTO_TEST_CASE(add_IncorrectValue_ExceptionThrown)
  {
    li::CompositeShape compShape(std::make_shared<li::Rectangle>(3.4, 1.2, alferova::point_t{ 3.4, 3.2 }));

    BOOST_CHECK_THROW(compShape.add(nullptr), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(getArea_ValidValues_ReturnsEqualValue)
  {
    double width = 2.1;
    double height = 3.0;
    double radius = 1.9;
    li::CompositeShape compShape(
        std::make_shared<alferova::Rectangle>(width, height, li::point_t{ 3.4, 3.2 }));

    compShape.add(std::make_shared<alferova::Circle>(radius, li::point_t{ 1.4, -3.2 }));

    BOOST_CHECK_CLOSE(compShape.getArea(), width * height + radius * radius * M_PI, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeScale_ExpectedBehaviorInWork)

  BOOST_AUTO_TEST_CASE(scale_InvalidValues_ExceptionThrown)
  {
    li::CompositeShape compShape(std::make_shared<li::Rectangle>(5.6, 5.6, alferova::point_t{ 3.4, 3.2 }));

    BOOST_CHECK_THROW(compShape.scale(0.0), std::invalid_argument);
    BOOST_CHECK_THROW(compShape.scale(-3.1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(positionAfterScale_ValidValues_ReturnsEqualValues)
  {
    li::CompositeShape compShape(std::make_shared<li::Rectangle>(2.0, 2.0, alferova::point_t{ 0.0, 0.0 }));
    li::point_t centerOfCompShape{ 1.0, 1.0 };

    compShape.add(std::make_shared<alferova::Circle>(1.0, li::point_t{ 2.0, 2.0 }));
    compShape.scale(3.5);

    BOOST_CHECK_CLOSE(centerOfCompShape.x, compShape.getPos().x, ACCURACY);
    BOOST_CHECK_CLOSE(centerOfCompShape.y, compShape.getPos().y, ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(getAreaAfterScale_ValidValues_CorrectCalculations)
  {
    double width = 2.0, height = 2.0;
    double radius = 1.0;
    li::CompositeShape compShape(
        std::make_shared<alferova::Rectangle>(width, height, li::point_t{ 1.4, 6.1 }));

    compShape.add(std::make_shared<li::Circle>(radius, li::point_t{ 2.3, 4.1 }));

    double coef = 1.9;
    compShape.scale(coef);

    BOOST_CHECK_CLOSE(( width * height + radius * radius * M_PI ) * coef * coef, compShape.getArea(), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(getAreaAfterScale_CoefIsOne_NothingChanged)
  {
    double width = 2.0, height = 2.0;
    double radius = 1.0;
    li::CompositeShape compShape(
        std::make_shared<li::Rectangle>(width, height, li::point_t{ 1.4, 6.1 }));
    compShape.add(std::make_shared<li::Circle>(radius, li::point_t{ 2.3, 4.1 }));

    double coef = 1.0;
    compShape.scale(coef);

    BOOST_CHECK_CLOSE(( width * height + radius * radius * M_PI ) * coef * coef, compShape.getArea(), ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeMove_ExpectedBehaviorInWork)

  BOOST_AUTO_TEST_CASE(moveToThePoint_ValidValues_ReturnsCorrectValue)
  {
    li::CompositeShape compShape(std::make_shared<li::Rectangle>(2.0, 2.0, alferova::point_t{ 0.0, 0.0 }));
    compShape.add(std::make_shared<li::Circle>(1.0, li::point_t{ 2.0, 2.0 }));
    li::point_t newPos{ 3.0, 5.0 };

    compShape.move(newPos);

    BOOST_CHECK_EQUAL(compShape.getPos().x, newPos.x);
    BOOST_CHECK_EQUAL(compShape.getPos().y, newPos.y);
  }

  BOOST_AUTO_TEST_CASE(moveByAxis_ValidValues_ReturnsCorrectValues)
  {
    double width = 2.0, height = 2.0;
    double radius = 1.0;
    double x1 = 0.0, y1 = 0.0;
    double x2 = 2.0, y2 = 2.0;
    li::CompositeShape compShape(
        std::make_shared<li::Rectangle>(width, height, li::point_t{ x1, y1 }));
    li::point_t centerOfCompShape{ 1.0, 1.0 };

    compShape.add(std::make_shared<li::Circle>(radius, li::point_t{ x2, y2 }));

    double dx = 1.8, dy = 5.1;
    compShape.move(dx, dy);

    BOOST_CHECK_CLOSE(centerOfCompShape.x + dx, compShape.getPos().x, ACCURACY);
    BOOST_CHECK_CLOSE(centerOfCompShape.y + dy, compShape.getPos().y, ACCURACY);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeRemove_ExpectedBehavior)

  BOOST_AUTO_TEST_CASE(remove_InvalidValue_ExceptionThrown)
  {
    li::CompositeShape compShape(std::make_shared<li::Rectangle>(2.0, 2.0, li::point_t{ 0.0, 0.0 }));

    BOOST_CHECK_THROW(compShape.remove(3), std::out_of_range);
    BOOST_CHECK_THROW(compShape.remove(compShape.getSize()), std::out_of_range);
    BOOST_CHECK_THROW(compShape.remove(0), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(remove_ValidValue_ReturnsCorrectSize)
  {
    li::CompositeShape compShape(std::make_shared<li::Rectangle>(2.0, 2.0, li::point_t{ 0.0, 0.0 }));

    compShape.add(std::make_shared<li::Circle>(1.0, li::point_t{ 2.0, 2.0 }));
    BOOST_CHECK_EQUAL(compShape.getSize(), 2);
    compShape.remove(1);
    BOOST_CHECK_EQUAL(compShape.getSize(), 1);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShapeOperatorIndex_ExpectedBehavior)

  BOOST_AUTO_TEST_CASE(OperatorIndex_ValidValues_ReturnsEqualPointers)
  {
    li::CompositeShape compShape(std::make_shared<li::Rectangle>(2.0, 2.0, li::point_t{ 0.0, 0.0 }));
    std::shared_ptr<li::Rectangle> recptr = std::make_shared<li::Rectangle>(3.0, 2.0,
         li::point_t{ 4.0, 0.5 });
    std::shared_ptr<li::Circle> cirptr = std::make_shared<li::Circle>(2.0, li::point_t{ 0.1, 7.0 });

    compShape.add(recptr);
    compShape.add(cirptr);

    BOOST_CHECK_EQUAL(compShape[1], recptr);
    BOOST_CHECK_EQUAL(compShape[2], cirptr);
  }

  BOOST_AUTO_TEST_CASE(OperatorIndex_InvalidValues_ExceptionThrown)
  {
    li::CompositeShape compShape(std::make_shared<li::Rectangle>(2.0, 2.0, li::point_t{ 0.0, 0.0 }));

    compShape.add(std::make_shared<li::Circle>(1.0, li::point_t{ 2.0, 2.0 }));

    BOOST_CHECK_THROW(compShape[5], std::out_of_range);
    BOOST_CHECK_THROW(compShape[-2], std::out_of_range);
    BOOST_CHECK_THROW(compShape[compShape.getSize()], std::out_of_range);
  }

BOOST_AUTO_TEST_SUITE_END()
