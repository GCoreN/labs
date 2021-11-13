#include <iostream>
#include <stdexcept>

#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "base-types.hpp"


void testAreaMovingShape(Shape& shape);

int main()
{
  Rectangle* rectanglePtr = nullptr; //Создаем указатель на прямоугольник для обработки исключения при его создании в 21 строке
  double x = 0.7;
  double y = 3.1;
  double width = 13.7;
  double height = 1.4;
  try
  {
    rectanglePtr = new Rectangle(width, height,{ x, y });
    /*Из-за области видимости блока try созданный прямоугольник
     * не был бы доступен, благодарая указателю все ок*/
  }
  catch (std::invalid_argument& exception)
  {
    std::cerr << "Constructor exception: " << exception.what();
    return 1;
  }
  std::cout << "Created rectangle in ( " << x << ", " << y << " )\n"
      << "width - " << width << " height - " << height <<'\n';

  testAreaMovingShape(*rectanglePtr);

  std::cout << "Creating a frame rectangle\n";
  rectangle_t frameRect = rectanglePtr->getFrameRect();
  std::cout << "Frame rectangle specifications:\n"
      << "height: " << frameRect.height << '\n'
      << "width: " << frameRect.width << '\n'
      << "position: ( " << frameRect.pos.x << ", " << frameRect.pos.y << " )\n";

  double x1 = 5.2;
  double y1 = 8.3;
  std::cout << "Moving the rectangle to the point ( " << x1 << ", " << y1 << " )\n";
  rectanglePtr->move({ x1, y1 });
  point_t position = rectanglePtr->getPos();
  std::cout << "Rectangle's position: ( " << position.x << ", " << position.y << " )\n";

  double dx = 11.0;
  double dy = -25.7;
  std::cout << "Moving the rectangle by coordinates: ( x + " << dx << ", y + " << dy << " )\n";
  rectanglePtr->move(dx, dy);
  position = rectanglePtr->getPos();
  std::cout << "Rectangle's position: ( " << position.x << ", " << position.y << " )\n";

  Circle* circlePtr = nullptr;
  x = 17.2;
  y = 3.6;
  double radius = 8.9;

  try
  {
    circlePtr = new Circle(radius, { x, y });
  }
  catch (std::invalid_argument& exception)
  {
    std::cerr << "Constructor exception: " << exception.what();
    delete rectanglePtr;
    return 1;
  }

  std::cout << "\nCreated a circle with radius = " << radius
      << " in the point ( " << x << ", " << y << " )\n";

  moveShape(*circlePtr);

  std::cout << "Creating a frame rectangle\n";
  frameRect = circlePtr->getFrameRect();
  std::cout << "Frame rectangle specifications:\n"
      << "height: " << frameRect.height << '\n'
      << "width: " << frameRect.width << '\n'
      << "position: ( " << frameRect.pos.x << ", " << frameRect.pos.y << " )\n";

  x1 = 11.1;
  y1 = 5.0;
  std::cout << "Moving the circle to the point ( " << x1 << ", " << y1 << " )\n";
  circlePtr->move({ x1, y1 });
  position = circlePtr->getPos();
  std::cout << "Circle's position: ( " << position.x << ", " << position.y << " )\n";

  dx = -10.3;
  dy = -1.2;
  std::cout << "Moving the circle by coordinates: ( x + " << dx << ", y + " << dy << " )\n";
  circlePtr->move(dx, dy);
  position = circlePtr->getPos();
  std::cout << "Circle's position: ( " << position.x << ", " << position.y << " )\n";
  
  delete rectanglePtr;
  delete circlePtr;
  return 0;
}

void testAreaMovingShape(Shape& shape) //Проверяем изменилась ли площадь после сдвига
{
  std::cout << "Shape's area is: " << shape.getArea() << '\n';

  double x = 1.7;
  double y = 5.9;
  shape.move({ x, y });

  std::cout << "Shape moved to the point ( " << x << ", " << y << " ), shape's area is: "
      << shape.getArea() << '\n';
}
