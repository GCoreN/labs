#include <iostream>
#include <stdexcept>
#include <memory>

#include "../common/base-types.hpp"
#include "../common/shape.hpp"
#include "../common/rectangle.hpp"
#include "../common/circle.hpp"
#include "../common/composite-shape.hpp"


void testAreaMovingShape(li::Shape &shape); //Проверяем изменилась ли площадь после сдвига

void printFrameRect(const li::Shape &shape); //Вывод информации о frameRect

void moveToThePoint(li::Shape &shape); //Сдвиг фигуры в заданную точку

void moveByCoordinates(li::Shape &shape); //Сдвиг фигуры на заданные координаты

void scaleShape(li::Shape &shape); //Увеличение\уменьшение фигуры

int main()
{
  std::unique_ptr<li::Rectangle> rectanglePtr = nullptr;

  double x = 0.1;
  double y = 2.7;
  double width = 10.0;
  double height = 3.1;

  try
  {
    rectanglePtr = std::make_unique<li::Rectangle>(width, height, li::point_t{ x, y });
  }
  catch (const std::invalid_argument &exception)
  {
    std::cerr << "Constructor exception: " << exception.what();
    return 1;
  }

  std::cout << "Created a rectangle in the point ( " << x << ", " << y << " )\n" << "width: " << width << " height: "
      << height << '\n';

  testAreaMovingShape(*rectanglePtr);
  printFrameRect(*rectanglePtr);
  moveToThePoint(*rectanglePtr);
  moveByAxis(*rectanglePtr);

  try
  {
    scaleShape(*rectanglePtr);
    std::cout << "New width: " << rectanglePtr->getWidth() << " new height: " << rectanglePtr->getHeight() << '\n';
  }
  catch (const std::invalid_argument &exception)
  {
    std::cerr << "Scale exception: " << exception.what();
    return 1;
  }

  std::unique_ptr<li::Circle> circlePtr = nullptr;
  x = 1.0;
  y = 3.5;
  double radius = 4.5;

  try
  {
    circlePtr = std::make_unique<li::Circle>(radius, li::point_t{ x, y });
  }
  catch (const std::invalid_argument &exception)
  {
    std::cerr << "Constructor error: " << exception.what();
    return 1;
  }

  std::cout << "\nCreated a circle with radius = " << radius << " in the point ( " << x << ", " << y << " )\n";

  testAreaMovingShape(*circlePtr);
  printFrameRect(*circlePtr);
  moveToThePoint(*circlePtr);
  moveByAxis(*circlePtr);

  try
  {
    scaleShape(*circlePtr);
    std::cout << "New radius: " << circlePtr->getRadius() << '\n';
  }
  catch (const std::invalid_argument &exception)
  {
    std::cerr << "Scale exception: " << exception.what();
    return 1;
  }

  std::cout << "\nCreating a composite shape:\n";
  std::unique_ptr<li::CompositeShape> compShape = std::make_unique<li::CompositeShape>(
      std::make_shared<li::Rectangle>(6.1, 4.0, li::point_t{ 3.7, 3.9 }));

  try
  {
    compShape->add(std::make_shared<li::Rectangle>(2.1, 3.0, li::point_t{ 3.4, 3.2 }));
    compShape->add(std::make_shared<li::Rectangle>(4.9, 1.1, li::point_t{ 7.3, -1.8 }));
    compShape->add(std::make_shared<li::Circle>(4.0, li::point_t{ -4.3, 5.7 }));
    compShape->add(std::make_shared<li::Circle>(1.7, li::point_t{ -3.5, 0.1 }));
  }
  catch (const std::invalid_argument &exception)
  {
    std::cerr << "CompositeShape constructing exception: " << exception.what();
    return 1;
  }

  std::cout << "Composite shape consists of " << compShape->getSize() << " shapes\n";
  testAreaMovingShape(*compShape);
  printFrameRect(*compShape);
  moveToThePoint(*compShape);
  moveByAxis(*compShape);

  std::cout << "Third shape of composite shape has a frame rectangle: \n";
  printFrameRect(*( *compShape )[3]);

  try
  {
    scaleShape(*compShape);
    std::cout << "New width of composite shape: " << compShape->getFrameRect().width << '\n'
        << "New height of composite shape: " << compShape->getFrameRect().height << '\n';
  }
  catch (const std::invalid_argument &exception)
  {
    std::cerr << "Scale exception: " << exception.what();
    return 1;
  }

  std::cout << "Removing shape from the composite shape\n";
  compShape->remove(1);
  std::cout << "Now there are " << compShape->getSize() << " shapes in the composite shape\n";

  return 0;
}

void testAreaMovingShape(li::Shape &shape)
{
  std::cout << "The shape's area is: " << shape.getArea() << '\n';

  double x = 2.0;
  double y = 3.4;
  shape.move({ x, y });

  std::cout << "Moved the shape to the point ( " << x << ", " << y << " ), the shape's area now is: "
      << shape.getArea() << '\n';
}

void printFrameRect(const li::Shape &shape)
{
  std::cout << "Creating a frame circumscribing the shape\n";
  li::rectangle_t frame = shape.getFrameRect();
  std::cout << "Parameters of the frame rectangle are:\n" << "height: " << frame.height << '\n' << "width: " << frame.width
      << '\n' << "position: ( " << frame.pos.x << ", " << frame.pos.y << " )\n";
}

void moveToThePoint(li::Shape &shape)
{
  double x = 2.4;
  double y = 4.7;
  std::cout << "Moving the shape to the point ( " << x << ", " << y << " )\n";
  shape.move({ x, y });
    li::point_t position = shape.getPos();
  std::cout << "new position of the shape: ( " << position.x << ", " << position.y << " )\n";
}

void moveByCoordinates(li::Shape &shape)
{
  double dx = 4.0;
  double dy = -5.1;
  std::cout << "Moving the shape by axis: ( x + " << dx << ", y + " << dy << " )\n";
  shape.move(dx, dy);
  li::point_t position = shape.getPos();
  std::cout << "new position of the shape: ( " << position.x << ", " << position.y << " )\n";
}

void scaleShape(li::Shape &shape)
{
  double coef = 3.1;
  li::point_t position = shape.getPos();
  std::cout << "Scaling the shape by coefficient: " << coef << '\n';
  shape.scale(coef);
  std::cout << "New area's value of the shape: " << shape.getArea() << '\n' << "new position of the shape: ( "
      << position.x << ", " << position.y << " )\n";
}
